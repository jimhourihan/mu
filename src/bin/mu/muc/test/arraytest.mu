
module: arraytest
{
    //
    //  Tests of array constants
    //

    \: dynamic_constant (int[];)
    {
        int[] {1,2,3,4,5};
    }

    \: fixed_constant (int[5];)
    {
        int[5] {1,2,3,4,5};
    }

    //
    //  Tests of runtime constructors
    //
    
    \: dynamic_constructor (int[]; int a)
    {
        int[] {a, a*2, a*3, a*4, a*5};
    }

    \: fixed_constructor (int[5]; int a)
    {
        int[5] {a, a*2, a*3, a*4, a*5};
    }

    //
    //  Indexing
    //

    \: index_test (int[]; int[] array)
    {
        //let array = int[] {1,2,3,4,5,6,7,8,9};
        for (int i=0; i < array.size(); i++)
        {
            array[i] = i;
        }

        return array;
    }
}
