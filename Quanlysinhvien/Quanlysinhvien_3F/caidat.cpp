#include "thuvien.h"

sinh_vien nhap_thong_tin(){
    sinh_vien tt;
    cout << "\t\t(?) Nhap ten: "; 
    getline(cin, tt.ho_ten);
    cout << "\t\t(?) Nhap tuoi: ";
    cin >> tt.tuoi;
    cin.ignore();
    cout << "\t\t(?) Nhap mssv: ";
    getline(cin, tt.mssv);
    cout << "\t\t(?) Nhap diem: ";
    cin >> tt.diem;
    cin.ignore();
    return tt;
}

// hàm load dữ liệu từ file (update thông tin)
vector<sinh_vien> doc_du_lieu_tu_file(const string& ten_file) {
    vector<sinh_vien> danh_sach;
    ifstream file(ten_file);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        sinh_vien tt;
        string tuoi_str, diem_str;
        getline(ss, tt.ho_ten, ';');
        getline(ss, tuoi_str, ';');
        getline(ss, tt.mssv, ';');
        getline(ss, diem_str, ';');
        tt.tuoi = stoi(tuoi_str);
        tt.diem = stof(diem_str);
        danh_sach.push_back(tt);
    }
    return danh_sach;
}

// in dong ra giua man hinh
void in_giua_man_hinh(const string& cau) {
    int chieu_rong = 120; // canh giữa màn hình terminal mini khoảng 120 
    int do_dai = cau.length();
    int khoang_trang = (chieu_rong - do_dai) / 2;
    if (khoang_trang < 0) khoang_trang = 0;
    cout << string(khoang_trang, ' ') << cau;
}

// 1 in theo danh sách 
void in_theo_danh_sach(const vector<sinh_vien>& danh_sach) {
    cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
    cout << "\t| STT | Ho Ten                         | Tuoi  | MSSV       | Diem  |\n";
    cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
    int stt = 1;
    for (const auto& tt : danh_sach) {
        cout << "\t| " << setw(3) << stt++ << " | "
             << setw(30) << left << tt.ho_ten << " | "
             << setw(5) << left << tt.tuoi << " | "
             << setw(10) << left << tt.mssv << " | "
             << setw(5) << fixed << setprecision(1) << tt.diem << " |\n";
    }
    cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
}


// ghi vào file sau khi nhap them thong tin sinh vien moi 
void ghi_vao_file(const string& ten_file, const vector<sinh_vien>& danh_sach) {
    ofstream file(ten_file);
    for (const auto& tt : danh_sach) {
        file << tt.ho_ten << ';' << tt.tuoi << ';' << tt.mssv << ';' << tt.diem << ";\n";
    }
}

// 2 them vao danh sach 
void them_vao_danh_sach(vector<sinh_vien>& danh_sach){
    cout << "\t(?) Nhap so luong sinh vien muon them: ";
    int slsv; cin >> slsv;
    cin.ignore();
    for(int i = 0; i < slsv; i++){
        cout << "\t(!) Sinh vien" << i + 1 << "\n";
        sinh_vien tt = nhap_thong_tin();
        danh_sach.pb(tt); // push_back (đẩy thông tin vào danh sách)
        ghi_vao_file("D:\\Quanlysinhvien\\Quanlysinhvien_3F\\danhsach.txt", danh_sach);
    }
    cout << "\t(*) Da them " << slsv << " sinh vien thanh cong !\n";
}

// 3 sua danh sach sinh vien 
void sua_danh_sach(vector<sinh_vien>& danh_sach){
    int stt; 
    cout << "\t(?) Nhap so thu tu muon sua thong tin: "; cin >> stt;
    cin.ignore();
    if(stt < 1 || stt > danh_sach.size()){
        cout << "\t(!) So thu tu khong hop le !\n";
        return;
    }
    sinh_vien& tt = danh_sach[stt-1];
    cout << "\t\t(?) Nhap ten moi (nhap enter bo qua neu khong sua): ";
    string ten_moi;
    getline(cin, ten_moi);
    if(!ten_moi.empty()){
        tt.ho_ten = ten_moi;
    }
    cout << "\t\t(?) Nhap tuoi moi (nhap 0 bo qua neu khong sua): ";
    int tuoi_moi; cin >> tuoi_moi;
    if(tuoi_moi > 0){
        tt.tuoi = tuoi_moi;
    }
    cin.ignore();
    cout << "\t\t(?) Nhap ma so sinh vien (nhap enter bo qua neu khong sua): ";
    string mssv_moi; 
    getline(cin, mssv_moi);
    if(!mssv_moi.empty()){
        tt.mssv = mssv_moi;
    }
    cout << "\t\t(?) Nhap diem moi (nhap -1 bo qua neu khong sua): ";
    float diem_moi;
    cin >> diem_moi;
    if (diem_moi >= 0) {
        tt.diem = diem_moi;
    }
    ghi_vao_file("D:\\Quanlysinhvien\\Quanlysinhvien_3F\\danhsach.txt", danh_sach);
    cin.ignore();
    cout << "\t(*) Da cap nhat thanh cong thong tin sinh vien so thu tu " << stt << "\n";
}

// 4 xóa sinh vien khoi danh sach
void xoa_sinh_vien(vector<sinh_vien>& danh_sach) {
    int stt;
    cout << "\t(?) Nhap so thu tu sinh vien muon xoa: "; cin >> stt;
    cin.ignore();
    if (stt < 1 || stt > danh_sach.size()) {
        cout << "\t(!) So thu tu khong hop le !\n";
        return;
    }
    danh_sach.erase(danh_sach.begin() + (stt - 1)); 
    sinh_vien& tt = danh_sach[stt-1];
    cout << "\t(*) Da xoa thong tin sinh vien " << tt.ho_ten << " - " << stt << " khoi danh sach\n";
    ghi_vao_file("D:\\Quanlysinhvien\\Quanlysinhvien_3F\\danhsach.txt", danh_sach);
}

// hàm chuyển ký tự sang ký tự thường (không có ký tự hoa)
void chuyen_ve_ky_tu_thuong(string& kytu) {
    transform(kytu.begin(), kytu.end(), kytu.begin(), ::tolower);
}

// 5 tim kiem thong tin sinh vien 
void tim_kiem_sinh_vien(vector<sinh_vien>& danh_sach){
    int lua_chon; 
    cout << "\t1 - tim kiem theo so thu tu\n";
    cout << "\t2 - tim kiem theo ky tu ten\n";
    cout << "\t3 - tim kiem theo mssv\n";
    cout << "\t(?) Nhap lua chon: "; cin >> lua_chon;
    if(lua_chon == 1){
        int stt; 
        cout << "\t(?) Nhap so thu tu muon tim kiem: "; cin >> stt;
        cin.ignore();
        if(stt < 1 || stt > danh_sach.size()){
            cout << "\t\t(!) So thu tu khong hop le !\n";
            return;
        }
        sinh_vien& tt = danh_sach[stt - 1];
        // cout << "\tThong tin sinh vien thu " << stt << " !\n";
        // cout << "\t(-->) Ho ten: " << tt.ho_ten << "\t(-->) Tuoi: " << tt.tuoi << "\t(-->) Diem: " << tt.diem << "\n"; 
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        cout << "\t| STT | Ho Ten                         | Tuoi  | MSSV       | Diem  |\n";
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        cout << "\t| " << setw(3) << stt << " | "
             << setw(30) << left << tt.ho_ten << " | "
             << setw(5) << left << tt.tuoi << " | "
             << setw(10) << left << tt.mssv << " | "
             << setw(5) << fixed << setprecision(1) << tt.diem << " |\n";
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
    } else if (lua_chon == 2){
        string nhap_ky_tu; 
        cout << "\t\t(?) Nhap ky tu muon tim kiem: "; cin >> nhap_ky_tu;
        cin.ignore();
        vector<sinh_vien> danh_sach_tim_kiem;
        for(const auto& tt : danh_sach){
            string ten_sv = tt.ho_ten;
            chuyen_ve_ky_tu_thuong(ten_sv);
            if(ten_sv.find(nhap_ky_tu) != string::npos){
                danh_sach_tim_kiem.pb(tt);
            }
        }  
        if (danh_sach_tim_kiem.empty()) {
            cout << "\t(!) Khong tim thay sinh vien nao phu hop!\n";
            return;
        }
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        cout << "\t| STT | Ho Ten                         | Tuoi  | MSSV       | Diem  |\n";
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        int stt = 1;
        for (const auto& tt : danh_sach_tim_kiem) {
            cout << "\t| " << setw(3) << stt++ << " | "
                 << setw(30) << left << tt.ho_ten << " | "
                 << setw(5) << left << tt.tuoi << " | "
                 << setw(10) << left << tt.mssv << " | "
                 << setw(5) << fixed << setprecision(1) << tt.diem << " |\n";
        }
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
    } else if (lua_chon == 3){
        string nhap_ky_tu;
        cout << "\t\t(?) Nhap mssv muon tim kiem: "; cin >> nhap_ky_tu;
        cin.ignore();
        vector<sinh_vien> danh_sach_tim_kiem;
        for(const auto& tt : danh_sach){
            string mssv = tt.mssv;
            if(mssv.find(nhap_ky_tu) != string::npos){
                danh_sach_tim_kiem.pb(tt);
            }
        }
        if(danh_sach_tim_kiem.empty()){
            cout << "\t(!) Khong tim thay sinh vien nao phu hop!\n";
            return;
        }
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        cout << "\t| STT | Ho Ten                         | Tuoi  | MSSV       | Diem  |\n";
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
        int stt = 1;
        for (const auto& tt : danh_sach_tim_kiem) {
            cout << "\t| " << setw(3) << stt++ << " | "
                 << setw(30) << left << tt.ho_ten << " | "
                 << setw(5) << left << tt.tuoi << " | "
                 << setw(10) << left << tt.mssv << " | "
                 << setw(5) << fixed << setprecision(1) << tt.diem << " |\n";
        }
        cout << "\t+-----+--------------------------------+-------+------------+-------+\n";
    } else cout << "\t(!) Vui long chon lai 1 -> 2\n";    
}

// 6 sap xep danh sach sinh vien   
void sap_xep_danh_sach(vector<sinh_vien>& danh_sach) {
    cout << "\t1 - Sap xep theo ten (A -> Z)\n";
    cout << "\t2 - Sap xep theo ten (Z -> A)\n";
    cout << "\t3 - Sap xep theo diem (Cao -> Thap)\n";
    cout << "\t4 - Sap xep theo diem (Thap -> Cao)\n";
    cout << "\t5 - Sap xep theo tuoi (Tang dan)\n";
    cout << "\t6 - Sap xep theo tuoi (Giam dan)\n";
    cout << "\t(?) Nhap lua chon: ";
    int lua_chon; 
    cin >> lua_chon;
    cin.ignore();
    if (lua_chon == 1) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            string ten_a = a.ho_ten;
            string ten_b = b.ho_ten;
            chuyen_ve_ky_tu_thuong(ten_a);
            chuyen_ve_ky_tu_thuong(ten_b);
            return ten_a < ten_b;
        });
        cout << "\t\t(*) Da sap xep theo ten (A-Z)\n";
    }
    else if (lua_chon == 2) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            string ten_a = a.ho_ten;
            string ten_b = b.ho_ten;
            chuyen_ve_ky_tu_thuong(ten_a);
            chuyen_ve_ky_tu_thuong(ten_b);
            return ten_a > ten_b;
        });
        cout << "\t\t(*) Da sap xep theo ten (Z-A)\n";
    }
    else if (lua_chon == 3) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            return a.diem > b.diem;
        });
        cout << "\t\t(*) Da sap xep theo diem (cao -> thap)\n";
    }
    else if (lua_chon == 4) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            return a.diem < b.diem;
        });
        cout << "\t\t(*) Da sap xep theo diem (thap -> cao)\n";
    }
    else if (lua_chon == 5) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            return a.tuoi < b.tuoi;
        });
        cout << "\t\t(*) Da sap xep theo tuoi (tang dan)\n";
    }
    else if (lua_chon == 6) {
        sort(danh_sach.begin(), danh_sach.end(), [](const sinh_vien& a, const sinh_vien& b) {
            return a.tuoi > b.tuoi;
        });
        cout << "\t\t(*) Da sap xep theo tuoi (giam dan)\n";
    }
    else {
        cout << "\t\t(!) Lua chon khong hop le!\n";
        return;
    }
    cout << "\t\t+-----+--------------------------------+-------+------------+-------+\n";
        cout << "\t\t| STT | Ho Ten                         | Tuoi  | MSSV       | Diem  |\n";
        cout << "\t\t+-----+--------------------------------+-------+------------+-------+\n";
        int stt = 1;
        for (const auto& tt : danh_sach) {
            cout << "\t\t| " << setw(3) << stt++ << " | "
                 << setw(30) << left << tt.ho_ten << " | "
                 << setw(5) << left << tt.tuoi << " | "
                 << setw(10) << left << tt.mssv << " | "
                 << setw(5) << fixed << setprecision(1) << tt.diem << " |\n";
        }
    cout << "\t\t+-----+--------------------------------+-------+------------+-------+\n";
    cout << "\tLuu noi dung da sap xep vao file (y/n): ";
    char lua_chon_ghi_vao_file; cin >> lua_chon_ghi_vao_file;
    if(lua_chon_ghi_vao_file == 'y'){
        ghi_vao_file("D:\\Quanlysinhvien\\Quanlysinhvien_1F\\danhsach.txt", danh_sach);
        cout << "\tBan da chon ghi vao file !\n";
    } else cout << "\tBan chon khong ghi vao file !\n";
}

// 7 Thong ke danh sach sinh vien
void thong_ke_danh_sach(vector<sinh_vien>& danh_sach){
    int hsg = 0, hsk = 0, hstb = 0, hsy = 0; 
    float tdcl = 0, diem_max = 0;
    for (const auto& tt : danh_sach) {
        if(tt.diem >= 8 && tt.diem <= 10) hsg++;
        else if(tt.diem >= 6.5 && tt.diem < 8) hsk++;
        else if(tt.diem >= 4.0 && tt.diem < 6.5) hstb++;
        else hsy++;
        tdcl += tt.diem;
        if(tt.diem > diem_max) diem_max = tt.diem;
    }
    int slsv = danh_sach.size();
    float diem_tbcl = (float)(tdcl / slsv);
    float tl_hsg = ((float)hsg / slsv) * 100;
    float tl_hsk = ((float)hsk / slsv) * 100;
    float tl_hstb = ((float)hstb / slsv) * 100;
    float tl_hsy = ((float)hsy / slsv) * 100;
    cout << "\t(!) Diem trung binh ca lop: " << fixed << setprecision(2) << diem_tbcl << "\n";
    cout << "\t(!) Ty le sinh vien gioi: " << (float)tl_hsg << "%\n";
    cout << "\t(!) Ty le sinh vien kha: " << (float)tl_hsk << "%\n";
    cout << "\t(!) Ty le sinh vien trung binh: " << (float)tl_hstb << "%\n";
    cout << "\t(!) Ty le sinh vien yeu: " << (float)tl_hsy << "%\n";
    cout << "\t(!) Danh sach sinh vien cao diem nhat lop (" << diem_max << ") gom:\n";
    cout << "\t[";
    int slcdnl = 0, check = 0;
    for(int i = 0; i < danh_sach.size(); i++){
        if(danh_sach[i].diem == diem_max){
            slcdnl++; 
        }
    }    
    for(int i = 0; i < danh_sach.size(); i++){
        if(danh_sach[i].diem == diem_max){
            cout << danh_sach[i].ho_ten;
            if(check != slcdnl - 1) cout << ", ";
            check++;
        }
    }    
    cout << "]\n";
}
