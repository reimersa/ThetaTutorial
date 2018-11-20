#open corresponding index.html file
filename = '../03_runtheta/Analysis/index.html'
infile = open(filename,'r')
lines = infile.readlines()
lineidx = 0
mylines = []
for line in lines:
    if '<tr><th>signal process</th><th>expected limit</th><th>expected limit (central 1sigma)</th><th>expected limit (central 2sigma)</th><th>observed limit</th></tr>' in line:
        mylineidx = lineidx
        while lines[mylineidx+1][0:8] == '<tr><td>':
            mylines.append(lines[mylineidx+1])
            mylineidx += 1

    lineidx += 1
# print mylines


#go through lines and extract limits for each masspoint
mass = []
expected = []
up_68 = []
down_68 = []
up_95 = []
down_95 = []
observed = []

for line in mylines:
    line = line.split('<tr><td>')[1]
    line = line.split('</td></tr>')[0]
    values = line.split('</td><td>')
    valueidx = 0
    for value in values:
        if '+-' in value:
            value = value.split(' +- ')[0]
            values[valueidx] = value
        elif '--' in value:
            value1 = value.split('--')[0]
            value2 = value.split('--')[1]
            values[valueidx] = value1
            values.insert(valueidx+1, value2)
        valueidx += 1
    mass.append(values[0])
    expected.append(values[1])
    down_68.append(values[2])
    up_68.append(values[3])
    down_95.append(values[4])
    up_95.append(values[5])
    observed.append(values[6])
    # print values

# print expected
#print observed
#print up_95

outname = 'Limits.txt'
outfile = open(outname,'w')
outfile.write(str(len(mass)))
outfile.write('\n')
idx = 0
for value in mass:
    outfile.write(str(mass[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in expected:
    outfile.write(str(expected[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in down_68:
    outfile.write(str(down_68[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in up_68:
    outfile.write(str(up_68[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in down_95:
    outfile.write(str(down_95[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in up_95:
    outfile.write(str(up_95[idx]))
    outfile.write(' ')
    idx += 1
outfile.write('\n')
idx = 0
for value in observed:
    outfile.write(str(observed[idx]))
    outfile.write(' ')
    idx += 1
