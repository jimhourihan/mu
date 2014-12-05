
static int
QVariant_toInt_int(Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QVariant arg0 = getqtype<QVariantType>(param_this);
    return arg0.toInt();
}

static NODE_IMPLEMENTATION(toInt, int)
{
    NODE_RETURN(QVariant_toInt_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}
