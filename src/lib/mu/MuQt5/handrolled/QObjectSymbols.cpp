
addSymbols( new Function(c, "findChild", findChild, None,
                         Return, ftn,
                         Parameters,
                         new Param(c, "this", ftn),
                         new Param(c, "name", "string"),
                         End),

            new Function(c, "setProperty", setProperty, None,
                         Return, "bool",
                         Parameters,
                         new Param(c, "this", ftn),
                         new Param(c, "name", "string"),
                         new Param(c, "value", "qt.QVariant"),
                         End),

            EndArguments);
