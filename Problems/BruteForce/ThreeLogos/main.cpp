/**
https://vjudge.net/contest/690986#problem/J
https://codeforces.com/problemset/problem/581/D

Three companies decided to order a billboard with pictures of their logos. A billboard is a big square board. A logo of each company is a rectangle of a non-zero area.

Advertisers will put up the ad only if it is possible to place all three logos on the billboard so that they do not overlap and the billboard has no empty space left. When you put a logo on the billboard, you should rotate it so that the sides were parallel to the sides of the billboard.

Your task is to determine if it is possible to put the logos of all the three companies on some square billboard without breaking any of the described rules.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution
{
public:
    std::vector<std::string> threeLogos(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
    {
        int area = (A[0] * A[1]) + (B[0] * B[1]) + (C[0] * C[1]);
        int side = (int)sqrt(area);
        if (side * side != area)
        {
            throw -1;
        }

        std::vector<std::string> logo(side, std::string(side, ' '));
        
        for (int i = 0; i < 2; i++)
        {
            std::swap(A[0], A[1]);
            for (int j = 0; j < 2; j++)
            {
                std::swap(B[0], B[1]);
                for (int k = 0; k < 2; k++)
                {
                    std::swap(C[0], C[1]);

                    if (checking(side, A, B, C, logo))
                    {
                        return logo;
                    }
                }
            }
        }

        throw -1;
    }
private:
    bool checking(int n, std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, std::vector<std::string>& logo)
    {
        // Check if A, B, and C can fit in a row
        if (A[0] + B[0] + C[0] == n && A[1] == n && B[1] == n && C[1] == n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < A[0]; j++)
                {
                    logo[i][j] = 'A';
                }
                for (int j = A[0]; j < A[0] + B[0]; j++)
                {
                    logo[i][j] = 'B';
                }
                for (int j = A[0] + B[0]; j < n; j++)
                {
                    logo[i][j] = 'C';
                }
            }
            return true;
        }

        // Check if A, B, and C can fit in a column
        if (A[1] + B[1] + C[1] == n && A[0] == n && B[0] == n && C[0] == n)
        {
            for (int i = 0; i < A[1]; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'A';
                }
            }
            for (int i = A[1]; i < A[1] + B[1]; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'B';
                }
            }
            for (int i = A[1] + B[1]; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'C';
                }
            }
            return true;
        }

        // Check if A and B can fit in a row and C in a column
        if (A[0] + B[0] == n && A[1] == B[1] && A[1] + C[1] == n && C[0] == n)
        {
            for (int i = 0; i < A[1]; i++)
            {
                for (int j = 0; j < A[0]; j++)
                {
                    logo[i][j] = 'A';
                }
                for (int j = A[0]; j < n; j++)
                {
                    logo[i][j] = 'B';
                }
            }
            for (int i = A[1]; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'C';
                }
            }
            return true;
        }

        // Check if A and C can fit in a row and B in a column
        if (A[0] + C[0] == n && A[1] == C[1] && A[1] + B[1] == n && B[0] == n)
        {
            for (int i = 0; i < A[1]; i++)
            {
                for (int j = 0; j < A[0]; j++)
                {
                    logo[i][j] = 'A';
                }
                for (int j = A[0]; j < n; j++)
                {
                    logo[i][j] = 'C';
                }
            }
            for (int i = A[1]; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'B';
                }
            }
            return true;
        }

        // Check if B and C can fit in a row and A in a column
        if (B[0] + C[0] == n && B[1] == C[1] && B[1] + A[1] == n && A[0] == n)
        {
            for (int i = 0; i < B[1]; i++)
            {
                for (int j = 0; j < B[0]; j++)
                {
                    logo[i][j] = 'B';
                }
                for (int j = B[0]; j < n; j++)
                {
                    logo[i][j] = 'C';
                }
            }
            for (int i = B[1]; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    logo[i][j] = 'A';
                }
            }
            return true;
        }

        return false;
    }
};

int main()
{
    std::vector<int> A(2);
    std::vector<int> B(2);
    std::vector<int> C(2);

    std::cin >> A[0] >> A[1];
    std::cin >> B[0] >> B[1];
    std::cin >> C[0] >> C[1];

    Solution sol;
    try
    {
        std::vector<std::string> logo = sol.threeLogos(A, B, C);
        std::cout << logo.size() << std::endl;
        for (const std::string& line : logo)
        {
            std::cout << line << std::endl;
        }
    }
    catch(const int& val)
    {
        std::cout << val << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "-1" << std::endl;
    }

    return 0;
}