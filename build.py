import os
import shutil
from typing import List
import logging

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
        logging.error('Please install the following tool/s {}'.format(req))
        return False
    return True

def build():
    root_path = os.path.abspath('.')
    target = 'build'
    p = os.path.join(root_path, target)
    status = False
    try:
        if os.path.isdir(p):
            logging.warning('Directory {} already exist'.format(p))
            logging.warning('Delete {} directory'.format(p))
            shutil.rmtree(p)
        logging.info('Create {} directory'.format(p))
        os.mkdir(p)
        logging.info('Execute cmake command')
        comamnd = 'cd {} && cmake .. && cmake --build ./'.format(target)
        logging.info('Command: {}'.format(comamnd))
        n = os.system(comamnd)
        if n != 0:
            raise(n)
        logging.info('Executable at {}'.format(p))
        status = True
    except:
        logging.error('Error encounter. Cleaning {} directory...'.format(p))
        if os.path.isdir(p):
            logging.info('Delete {}'.format(p))
            shutil.rmtree(p)
    finally:
        return status

if __name__ == '__main__':
    requires = ['cmake']
    logging.basicConfig(level=logging.INFO  , format='%(asctime)s - %(levelname)-8s - %(message)s')
    logging.info('Checking requirements... [requires: {}]'.format(requires))
    if not check_requirements(requires):
        logging.error('Requirements not satisfied')
        exit(1)
    logging.info('Requirements satisfied')
    logging.info('Build started...')
    if build():
        logging.info('Build successfully completed')
        exit(0)
    logging.error('Build failed.')
    exit(1)
