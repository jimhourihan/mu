
module: colortest
{

    Vec3 := vector float[3];

\: toRGB (Vec3; float h, float s, float v)
{
    let r = 0.0,
        g = 0.0,
        b = 0.0;

    if (s == 0.0) 
    {
	r = g =	b = v;
    }
    else 
    {
	if (h == 1.0) h	= 0.0;
	float H = h * 6.0;
	int i   = int(math.floor(H));
        if (i > 5 || i < 0) i = 0;
	float f = H - i;
	float p = v * (1.0 - s);
	float q = v * (1.0 - (s * f));
	float t = v * (1.0 - (s * (1.0 - f)));

        if      (i == 0) { r = v; g = t; b = p; }
        else if (i == 1) { r = q; g = v; b = p; }
        else if (i == 2) { r = p; g = v; b = t; }
        else if (i == 3) { r = p; g = q; b = v; }
        else if (i == 4) { r = t; g = p; b = v; }
        else if (i == 5) { r = v; g = p; b = q; }
        //else 
        //{ 
            //print("i = %d\n" % i);
        //}
    }

    Vec3(r,g,b);
}

}
