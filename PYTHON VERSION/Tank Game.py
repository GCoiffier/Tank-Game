# Tank Game:
# A game with tanks and stuff.
#
# by Guillaume Coiffier & Florimond Manca
#
# Main file
import sys
import os

src_path = os.path.join(os.getcwd(),"src")
if src_path not in sys.path :
    sys.path.append(src_path)

from Menu import *
from Training import *

#run_training()
run_game()

sys.path.remove(src_path)
