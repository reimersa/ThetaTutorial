#Build a model from histograms in inputfile
model = build_model_from_rootfile('../02_thetainput/theta_histograms.root',include_mc_uncertainties = True)

# In case there are empty bins in the background, fill them with a very small number (e.g. 1E-5) to avoid divergencies
model.fill_histogram_zerobins()

# Tell the model how we called our signal, all other samples will be background. Data always has to be named XYZ__DATA__XYZa
model.set_signal_processes('SIG*')

# now we can add systematic uncertainties affecting ONLY the shape of a process but not its shape. They are recommended to have a log-normal prior distribution
# for p in model.processes:
	# if p != "DATA":
		# Assume an uncertainty on the lumi of 5%. Data does not have this uncertainty of course!
		# This line adds an uncertainty to all observables (there is only one, M_ll, in our case) of process p (SIG1, ..., BKG1, BKG2).
		# model.add_lognormal_uncertainty('lumi', math.log(1.05), p)

for o in model.observables:
	# Now add uncertainties on the cross sections of our backgrounds. In general, this has to be done individually for each background.
	model.add_lognormal_uncertainty('xsec_bkg1', math.log(1.3), 'BKG1', o)
	model.add_lognormal_uncertainty('xsec_bkg2', math.log(1.1), 'BKG2', o)

# Let theta calculate bayesian limits
# results = bayesian_limits(model, 'expected', n_toy = 3000)
# results = bayesian_limits(model, 'all', n_toy = 3000, n_data = 3000)

# If running on the NAF or similar, we can exploit multi-threading!
opt_nthread = Options()
opt_nthread.set('main', 'n_threads', '20')

# Write results to output file
# results = bayesian_limits(model, 'expected', n_toy = 3000, options = opt_nthread)
results = bayesian_limits(model, 'all', n_toy = 3000, n_data = 300, options = opt_nthread)

# Now perform the MLE fit alone
# Background-only, otherwise one can specify a signal or calculate for the default (all signals separately)
sig = ''
sig_a = []
mle_results = mle(model,'data', 1, signal_process_groups = {sig: sig_a})

# Signal + background (might not converge easily...)
# mle_results = mle(model,'data', 1)

parameter_values = {}
for p in model.get_parameters([]):
    parameter_values[p] = mle_results[''][p][0][0]
histos = evaluate_prediction(model, parameter_values, include_signal = False)
write_histograms_to_rootfile(histos, '../04_thetaoutput/postfit_histograms.root')

print '\n \nMLE fit results'
print '===============\n'
fitres = {}
print 'MLE values mean and dev'
file1 = open('../04_thetaoutput/MLEPostfit.txt', 'w')
for p in model.get_parameters(sig_a):
    mean = sdev = 0.0
    for pair in mle_results[sig][p]:
        mean += pair[0]
        sdev += pair[1]
    mean /= len(mle_results[sig][p])
    sdev /= len(mle_results[sig][p])
    fitres[p] = {}
    fitres[p][0] = mean
    fitres[p][1] = sdev
    line = ''
    if mean>=0: line += ' '
    line += ' %.3f' % mean + '  %.3f' % sdev + '  ' + p
    print line
    file1.write(line+'\n')
print '\n'

model_summary(model)
