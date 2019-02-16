#include <iostream>
#include <string>
#include <vector>

int main()
{
    freopen("planaritycheck.in", "r", stdin);
    freopen("planaritycheck.out", "w", stdout);
    int n;
    std::string s2;
    std::getline(std::cin, s2);
    n = atoi(s2.c_str());
    std::string s;
    std::vector<std::string> k5{"001011011101111", "010101101110111", "100110110111011", "111000111011101", "111111000011110", "111111111100000"};
    std::vector<std::string> k33{"000111111011100", "011001110111010", "011110001111001", "011110110000111", "101010101110110", "101101101001011",
                                 "101101010110101", "110011011010011", "110011100101101", "110100011101110"};
    for (int i = 0; i < n; ++i)
    {
        std::getline(std::cin, s);
        if (s.size() < 10)
        {
            std::cout << "YES\n";
        }
        if (s.size() == 10)
        {
            bool check = true;
            if (s == "1111111111")
            {
                check = false;
            }
            if (check)
            {
                std::cout << "YES\n";
            }
            else
            {
                std::cout << "NO\n";
            }
        }

        if (s.size() == 15)
        {
            bool check = true;
            for (int j = 0; j < k33.size(); ++j)
            {
                bool check2 = true;;
                std::string s1 = k33[j];
                for (int l = 0; l < 15; ++l)
                {
                    if (s1[l] == '1' && s[l] == '0')
                    {
                        check2 = false;
                    }
                }
                if (check2)
                {
                    check = false;
                }
            }
            for (int j = 0; j < k5.size(); ++j)
            {
                bool check2 = true;
                std::string s1 = k5[j];
                for (int l = 0; l < 15; ++l)
                {
                    if (s1[l] == '1' && s[l] == '0')
                    {
                        check2 = false;
                    }
                }
                if (check2)
                {
                    check = false;
                }
            }
            std::vector<int> q(6, 0);
            if (s[0] == '1')
            {
                ++q[0];
                ++q[1];
            }if (s[1] == '1')
            {
                ++q[0];
                ++q[2];
            }if (s[2] == '1')
            {
                ++q[1];
                ++q[2];
            }if (s[3] == '1')
            {
                ++q[0];
                ++q[3];
            }if (s[4] == '1')
            {
                ++q[1];
                ++q[3];
            }if (s[5] == '1')
            {
                ++q[2];
                ++q[3];
            }if (s[6] == '1')
            {
                ++q[0];
                ++q[4];
            }if (s[7] == '1')
            {
                ++q[1];
                ++q[4];

            }if (s[8] == '1')
            {
                ++q[2];
                ++q[4];
            }if (s[9] == '1')
            {
                ++q[3];
                ++q[4];
            }if (s[10] == '1')
            {
                ++q[0];
                ++q[5];
            }if (s[11] == '1')
            {
                ++q[1];
                ++q[5];
            }if (s[12] == '1')
            {
                ++q[2];
                ++q[5];
            }if (s[13] == '1')
            {
                ++q[3];
                ++q[5];
            }if (s[14] == '1')
            {
                ++q[4];
                ++q[5];
            }
            int countt = 0;
            for (int j = 0; j < 6; ++j)
            {
                if (q[j] == 4)
                {
                    ++countt;
                }
            }
            if (countt == 5)
            {
                check = false;
            }
            if (check)
            {
                std::cout << "YES\n";
            }
            else
            {
                std::cout << "NO\n";
            }
        }
    }
    return 0;
}