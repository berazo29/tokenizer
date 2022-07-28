import os
from sys import path
import shutil
from typing import List

def check_requirements(requires: List[str]) -> bool:

    def _chech_requirements(requires: List[str]) -> List[str]:
            if len(requires) == 0:
                return []
            
            req = []
            for r in requires:
                if shutil.which(r) is None:
                    req.append(r)
            return req

    req = _chech_requirements(requires)
    if len(req) != 0:
        print('Please install the following tool/s {}'.format(req))
        return False
    return True

def build():
    root_path = os.path.abspath('.')
    target = 'build'
    p = os.path.join(root_path, target)
    status = False
    try:
        if os.path.isdir(p):
            print('Delete {}'.format(p))
            shutil.rmtree(p)
        print('Create {}'.format(p))
        os.mkdir(p)
        print('Generate {} directory'.format(target))
        n = os.system('cd {} && cmake .. && cmake --build .'.format(target))
        if n != 0:
            raise(n)
        print('Executable at {}'.format(p))
        status = True
    except:
        print('Error encounter. Cleaning {} directory...'.format(p))
        if os.path.isdir(p):
            print('Delete {}'.format(p))
            shutil.rmtree(p)
    finally:
        return status

if __name__ == '__main__':
    requires = ['cmake']
    if check_requirements(requires):
        print('Building...')
        if build():
            print('Built successfully.')
            exit(0)

    print('Built fail.')
    exit(1)
