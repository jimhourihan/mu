use math in
{
    \: G (float; float a, float b) 
        let x = a, 
            y = b * b 
        in 
            x / sin(y) + y * cos(x);

    \: F (float; float a, float b) 
    {
        let x = a, 
            y = b * b;
        
        x / sin(y) + y * cos(x);
    };

    G(1.0, 2.0) == F(1.0, 2.0)
}
