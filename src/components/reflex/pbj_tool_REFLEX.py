import pbj_tools
from pbj_ninja import Rule

_reflex_rule = """
rule reflex
    command = $reflex $relexflags -o $out $in --header-file=$header_out
    description = generating reflex lexer $out
"""

class REFLEX_Tool (pbj_tools.GeneratorTool):
    def __init__ (self):
        self.rule = Rule(_reflex_rule)

    def name (self):
        return "REFLEX"

    def aux_outputs (self, platform, vars):
        return None

    def ninja_variable_block (self, platform, vars):
        blob = "reflex = $bin_dir/reflex\n"
        reflexflags = ""
        if 'REFLEX_PREFIX' in vars:
            p = vars['REFLEX_PREFIX']
            reflexflags += f" -P{p} "
        reflexflags += self.flags(vars)
        blob += f"reflexflags = {reflexflags}\n"
        return blob

    def ninja_primary_rule (self, platform, vars):
        return self.rule

def create ():
    return REFLEX_Tool()
