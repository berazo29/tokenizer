import os
from sys import path
import shutil

root_path = os.path.abspath('.')
target = 'build'
p = os.path.join(root_path, target)

# Run auto build
if os.path.isdir(p):
    print('Delete {}'.format(p))
    shutil.rmtree(p)
print('Create {}'.format(p))
os.mkdir(p)
print('Generate {} directory'.format(target))
os.system('cd {} && cmake .. && cmake --build .'.format(target))
print('Executable at {}'.format(p))