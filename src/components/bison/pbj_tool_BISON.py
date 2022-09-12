import pbj_tools
from pbj_ninja import Rule

_bison_rule = """
rule bison
    command = $bison $bisonflags -o $out $in --defines=$header_out
    description = generating bison grammar $out
"""

class BISON_Tool (pbj_tools.GeneratorTool):
    def __init__ (self):
        self.rule = Rule(_bison_rule)

    def name (self):
        return "BISON"

    def aux_outputs (self, platform, vars):
        return "location.hh"

    def ninja_variable_block (self, platform, vars):
        blob = "bison = $bin_dir/bison\n"
        bisonflags = "-dv "
        if 'BISON_PREFIX' in vars:
            p = vars['BISON_PREFIX']
            bisonflags += f" -p {p} "
        bisonflags += self.flags(vars)
        blob += f"bisonflags = {bisonflags}\n"
        return blob

    def ninja_primary_rule (self, platform, vars):
        return self.rule

def create ():
    return BISON_Tool()
