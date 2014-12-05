use io;

let file = ofstream("/tmp/test.binary");
file.write(byte(1));
file.write(byte(2));
file.write(byte(3));

string s = "hello world";
byte[] bytes;

for (int i=0; i < s.size(); i++)
{
    bytes.push_back(s[i]);
}

file.write(bytes);
file.close();
