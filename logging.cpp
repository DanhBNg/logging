#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
using namespace std;

class Logger {
    public:

        Logger(ostream& out) : out(out) {}

        void log(const string& msg) {
            out << msg << endl;
        }

    private:
        ostream& out;
};


class Matrix {
    public:

        Matrix(int hang, int cot) : hang(hang), cot(cot) {

            du_lieu.resize(hang);
            for (int i = 0; i < hang; i++) {
                du_lieu[i].resize(cot, 0);
            }
        }

        int get_hang() const {
            return hang;
        }

        int get_cot() const {
            return cot;
        }

        int get_phan_tu(int i, int j) const {
            if (i < 0 || i >= hang || j < 0 || j >= cot) {
                throw out_of_range("Chi so ngoai pham vi");
            }
            return du_lieu[i][j];
        }

        void set_phan_tu(int i, int j, int gia_tri) {
            if (i < 0 || i >= hang || j < 0 || j >= cot) {
                throw out_of_range("Chi so ngoai pham vi");
            }
            du_lieu[i][j] = gia_tri;
        }

        void print() const {
            for (int i = 0; i < hang; i++) {
                for (int j = 0; j < cot; j++) {
                    cout << du_lieu[i][j] << " ";
                }
                cout << endl;
            }
        }

        Matrix operator+(const Matrix& other) const {
            if (hang != other.hang || cot != other.cot) {
                throw invalid_argument("Ma tran phai co cung kich thuoc");
            }
            Matrix result(hang, cot);
            for (int i = 0; i < hang; i++) {
                for (int j = 0; j < cot; j++) {
                    result.du_lieu[i][j] = du_lieu[i][j] + other.du_lieu[i][j];
                }
            }
            return result;
        }


        Matrix operator-(const Matrix& other) const {
            if (hang != other.hang || cot != other.cot) {
                throw invalid_argument("Ma tran phai co cung kich thuoc");
            }
            Matrix result(hang, cot);

            for (int i = 0; i < hang; i++) {
                for (int j = 0; j < cot; j++) {
                    result.du_lieu[i][j] = du_lieu[i][j] - other.du_lieu[i][j];
                }
            }

            return result;
        }

        Matrix operator*(const Matrix& other) const {
 
            if (cot != other.hang) {
                throw invalid_argument("Ma tran phai co kich thuoc tuong thich");
            }

            Matrix result(hang, other.cot);

            for (int i = 0; i < hang; i++) {
                for (int j = 0; j < other.cot; j++) {
                    for (int k = 0; k < cot; k++) {
                        result.du_lieu[i][j] += du_lieu[i][k] * other.du_lieu[k][j];
                    }
                }
            }
            return result;
        }

        Matrix operator/(const Matrix& other) const {

            if (hang != other.hang || cot != other.cot) {
                throw invalid_argument("Ma tran phai co cung kich thuoc");
            }

            Matrix result(hang, cot);
            for (int i = 0; i < hang; i++) {
                for (int j = 0; j < cot; j++) {
                    if (other.du_lieu[i][j] == 0) {
                        throw invalid_argument("Khong the chia cho khong");
                    }
                    result.du_lieu[i][j] = du_lieu[i][j] / other.du_lieu[i][j];
                }
            }

            return result;
        }

    private:

        int hang, cot;

        vector<vector<int>> du_lieu;
};


Matrix nhap_ma_tran() {

    int hang, cot;
    cout << "Nhap so hang cua ma tran: ";
    cin >> hang;
    cout << "Nhap so cot cua ma tran: ";
    cin >> cot;

    Matrix ma_tran(hang, cot);

    cout << "Nhap cac phan tu cua ma tran:" << endl;
    for (int i = 0; i < hang; i++) {
        for (int j = 0; j < cot; j++) {
            int gia_tri;
            cin >> gia_tri;
            ma_tran.set_phan_tu(i, j, gia_tri);
        }
    }

    return ma_tran;
}

void xuat_ma_tran(const Matrix& ma_tran) {

    int hang = ma_tran.get_hang();
    int cot = ma_tran.get_cot();

    cout << "Ma tran co " << hang << " hang va " << cot << " cot:" << endl;
    for (int i = 0; i < hang; i++) {
        for (int j = 0; j < cot; j++) {
            cout << ma_tran.get_phan_tu(i, j) << " ";
        }
        cout << endl;
    }
}


int main() {
    Logger logger(cout);

    logger.log("Nhap ma tran A:");
    Matrix A = nhap_ma_tran();
    logger.log("Nhap ma tran B:");
    Matrix B = nhap_ma_tran();

    logger.log("Ma tran A:");
    xuat_ma_tran(A);
    logger.log("Ma tran B:");
    xuat_ma_tran(B);

    try {
        logger.log("A + B:");
        Matrix C = A + B;
        xuat_ma_tran(C);

        logger.log("A - B:");
        Matrix D = A - B;
        xuat_ma_tran(D);

        logger.log("A * B:");
        Matrix E = A * B;
        xuat_ma_tran(E);

        logger.log("A / B:");
        Matrix F = A / B;
        xuat_ma_tran(F);
    }
    catch (exception& e) {
        logger.log(e.what());
    }

    return 0;
}
