import os
cur_dir = os.path.dirname(os.path.realpath(__file__))
def local_file(filename):
    return os.path.join(cur_dir, filename)