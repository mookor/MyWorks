using System;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.IO;
namespace SHA256__MD5
{
    class MD5_SHA256
    {
        static void readbytes(ref byte[] bytes)
        {
            Console.WriteLine("Enter the name of file: ");
            string pathSource = Console.ReadLine();
            using (FileStream fsSource = new FileStream(pathSource, FileMode.Open, FileAccess.Read))
            {
                bytes = new byte[fsSource.Length];
                int numBytesToRead = (int)fsSource.Length;
                int numBytesRead = 0;
                while (numBytesToRead > 0)
                {
                    int n = fsSource.Read(bytes, numBytesRead, numBytesToRead);
                    if (n == 0)
                        break;

                    numBytesRead += n;
                    numBytesToRead -= n;
                }
                numBytesToRead = bytes.Length;
            }
        }

        static string calc_md5(byte[] bytes)
        {

            HashAlgorithm md5 = new MD5CryptoServiceProvider();
            byte[] hash_md5 = md5.ComputeHash(bytes);
            string res_md5 = BitConverter.ToString(hash_md5).Replace("-", "");
            return res_md5;
        }
        static string calc_sha256(byte[] bytes)
        {

            HashAlgorithm sha256 = new SHA256CryptoServiceProvider();
            byte[] hash_sha256 = sha256.ComputeHash(bytes);
            string res_sha256 = BitConverter.ToString(hash_sha256).Replace("-", "");
            return res_sha256;
        }

        static void Main(string[] args)
        {
            byte[] bytes = new byte[] { };
            string res_sha256, res_md5;
            readbytes(ref bytes);
            res_md5 = calc_md5(bytes);
            res_sha256 = calc_sha256(bytes);
            Console.WriteLine("MD5: " + res_md5);
            Console.WriteLine("SHA256: " + res_sha256);
            Console.Read();
        }

    }
}
