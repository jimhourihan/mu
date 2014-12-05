use io;

(float;float) F = \: (float;float a) { a + 68; };

let ofile = ofstream("/tmp/test.muc");
let n = serialize(ofile, F);
ofile.close();
n;

let ifile = ifstream("/tmp/test.muc");
(float;float) G = deserialize(ifile);
ifile.close();
G(1.0);
