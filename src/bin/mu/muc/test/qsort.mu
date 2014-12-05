
require math;

\: foo (int; int a, int b, float c, float d) 
{ 
    let q = c * a + b; 
    math.pow(q, 1.2) * bar(d);
}

\: bar (int; float a)
{
    return a * a;
}


operator: <= (bool; string a, string b) { compare(a, b) <= 0; }
operator: >= (bool; string a, string b) { compare(a, b) >= 0; }

function: qsort (void; string[] a, int lo, int hi)
{
    if (lo < hi) 
    {
        let l = lo,
            h = hi,
            p = a[hi];

        do 
        {
            while (l < h && a[l] <= p) l++;
            while (h > l && a[h] >= p) h--;

            if (l < h) 
            {
                let t = a[l];
                a[l] = a[h];
                a[h] = t;
            }

        } while (l < h);

        let t = a[l];
        a[l] = a[hi];
        a[hi] = t;

        qsort(a, lo, l-1);
        qsort(a, l+1, hi);
    }
}


function: sort (string[]; string[] array)
{
    string[] rbuffer = string[](array);
    qsort(rbuffer, 0, rbuffer.size() - 1);
    rbuffer;
}


foo(1,2,3,4);

//sort(string[] {"bee", "cee", "aye"});

