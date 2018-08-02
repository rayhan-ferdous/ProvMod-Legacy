from tools import remove_comments
from tools import fn_start_inspect
from tools import fn_inject
from tools import fn_inject_inspect

# main file
# |
# V

#remove_comments('CRHMmain.cpp', 'CRHMmain_nocom.cpp')

# file without comments
# |
# V

#fn_start_inspect('CRHMmain_nocom.cpp')
# manually save the file by modifying lines if necessary

# inspection in no comments file and modified version (a new one or overwritten one)
# |
# V

fn_inject('CRHMmain_nocom.cpp', 'CRHMmain_injected.cpp')

# code injected file
# |
# v

#fn_inject_inspect('CRHMmain_injected.cpp')

# soft inspection of injected file