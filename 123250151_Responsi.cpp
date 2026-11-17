// 123250151 - Fadhlan AKmal Insani
#include <iostream>
using namespace std;

struct Node{
    /* data */
    int kode;
    string nama;
    Node *next;
};

struct BST{
    int kode;
    string nama;
    BST *right;
    BST *left;
};

Node *headAntrian = nullptr;
Node *tailAntrian = nullptr;
Node *headTerserap= nullptr;

BST *rootOrgan = nullptr;

BST *insertOrgan(BST *root, int kode, string nama){
    if(root == nullptr){
        BST *newNode = new BST();
        newNode->kode = kode;
        newNode->nama = nama;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    if(kode < root->kode){
        root->left = insertOrgan(root->left, kode, nama);
    } else if(kode > root->kode){
        root->right = insertOrgan(root->right, kode, nama);
    }

    return root;


}

void preOrder(BST *root){
    if(root == nullptr) return;

    cout<<"["<<root->kode<<"] "<<root->nama<<endl;
    preOrder(root->left);
    preOrder(root->right);

}

void inOrder(BST *root){
    if(root == nullptr) return;

    inOrder(root->left);
    cout<<"["<<root->kode<<"] "<<root->nama<<endl;
    inOrder(root->right);

}

void postOrder(BST *root){
    if(root == nullptr) return;

    postOrder(root->left);
    postOrder(root->right);
    cout<<"["<<root->kode<<"] "<<root->nama<<endl;

}

void tambahEnergi(){
    char lagi;
    
    do{
        int kode;
        string nama;
        cout<<"Kode Energi : "; cin>>kode;
        cin.ignore();
        cout<<"Nama Energi : "; getline(cin, nama);

        if(kode <= 0){
            cout<<"Kode harus berupa angka > 0\n";
            system("pause");
            return;
        }

        Node *bantu = headAntrian;
        while(bantu != nullptr){
            if(bantu->kode == kode){
                cout<<"Kode sudah terpakai\n";
                system("pause");
                return;
            }
            bantu = bantu->next;
        }

        bantu = headTerserap;
        while(bantu != nullptr){
            if(bantu->kode == kode){
                cout<<"Kode sudah terpakai!\n";
                system("pause");
                return;
            }
            bantu = bantu->next;
        }

        Node *newNode = new Node();
        newNode->kode = kode;
        newNode->nama = nama;
        newNode->next = nullptr;

        if(headAntrian == nullptr){
            headAntrian = newNode;
            tailAntrian = newNode;
        } else{
            tailAntrian->next = newNode;
            tailAntrian = newNode;
        }

        cout<<"Berhasil menambahkan energi ke dalam antrian..\n";
        cout<<"Ingin menambahkan energi lagi (y/n): "; cin>> lagi;

        cout<<endl<<endl;

        } while(lagi == 'y' || lagi == 'Y');
}

void lihatAntrian(){
    cout<<endl;
    
    if(headAntrian == nullptr){
        cout<<"Tidak ada energi dalam antrian!\n";
        system("pause");
        return;
    }
    cout<<"=== Lihat Energi dalam Antrian ===\n";

    Node *bantu = headAntrian;
    int i = 1;
    while(bantu != nullptr){
        cout<<i<<". ["<<bantu->kode<<"] "<<bantu->nama<<endl;
        i++;
        bantu = bantu->next;
    }

    system("pause");
}

void prosesEnergi(){
    if(headAntrian == nullptr){
        cout<<"Tidak ada energi dalam antrian yang bisa diproses!\n";
        system("pause");
        return;
    }

    Node *diproses = headAntrian;
    if(headAntrian == tailAntrian){
        headAntrian = nullptr;
        tailAntrian = nullptr;
    } else{
        headAntrian = headAntrian->next;
    }

    rootOrgan = insertOrgan(rootOrgan, diproses->kode, diproses->nama);
    diproses->next = headTerserap;
    headTerserap = diproses;

    cout<<"Berhasil memproses energi "<<diproses->nama<<"!\n";
    system("pause");

}

void lihatEnergiTerserap(){
    if(headTerserap == nullptr){
        cout<<"Tidak ada energi yang sudah terserap!\n";
        system("pause");
        return;
    }

    cout<<"=== Energi yang Sudah Terserap ===\n";
    int i=1;
    Node *bantu = headTerserap;
    while(bantu != nullptr){
        cout<<i<<". "<<"["<<bantu->kode<<"] "<<bantu->nama<<endl;
        i++;
        bantu = bantu->next;
    }

    system("pause");

}

void hapusEnergiTerserap(){
    if(headTerserap == nullptr){
        cout<<"Tidak ada energi yang sudah terserap!\n";
        system("pause");
        return;
    }

    Node *hapus = headTerserap;
    headTerserap = headTerserap->next;

    cout<<"Riwayat energi "<<hapus->nama<<" teratas telah dihapus!\n";
    delete hapus;

    system("pause");

}

void cariEnergidiOrgan(){
    if(rootOrgan == nullptr){
        cout<<"Organ masih kosong!\n";
        system("pause");
        return;
    }

    int cari;
    cout<<"Masukkan Kode Energi : "; cin>>cari;

    if(cari <= 0){
        cout<<"Kode harus berupa angka > 0\n";
        system("pause");
        return;
    }

    BST *bantu = rootOrgan;
    while(bantu != nullptr){
        if(bantu->kode == cari){
            cout<<"Ditemukan : ["<<bantu->kode<<"] "<<bantu->nama<<endl;
            system("pause");
            return;
        } else if(cari < bantu->kode){
            bantu = bantu->left;
        } else{
            bantu = bantu->right;
        }
    }

    cout<<"Energi dengan kode "<<cari<<" tidak ditemukan di rak!\n";
    system("pause");

}

void lihatOrgan(){
    if(rootOrgan == nullptr){
        cout<<"Organ masih kosong!\n";
        system("pause");
        return;
    }

    int pilihan;
    cout<<"=== Isi Kristal Organ ===\n";
    cout<<"1. Pre-Order\n";
    cout<<"2. In-Order\n";
    cout<<"3. Post-Order\n";

    cout<<"Masukkan pilihan anda : "; cin>>pilihan;

    cout<<endl;

    switch (pilihan)
    {
    case 1:
        /* code */
        preOrder(rootOrgan);
        break;
    case 2:
        inOrder(rootOrgan);
        break;
    case 3:
        postOrder(rootOrgan);
        break;
    
    default:
        cout<<"Pilihan tidak tersedia\n";
        system("pause");
        break;
    }

    system("pause");

}

void gunakanEnergi(){
    if(rootOrgan == nullptr){
        cout<<"Organ masih kosong!\n";
        system("pause");
        return;
    }

    int kode;
    cout<<"Masukkan Kode Energi yang Ingin Digunakan: "; cin>>kode;

    if(kode <= 0){
        cout<<"Kode harus berupa angka > 0\n";
        system("pause");
        return;
    }

    BST *curr = rootOrgan;
    BST *parent = nullptr;

    while(curr != nullptr && curr->kode != kode){
        parent = curr;
        if(kode < curr->kode){
            curr = curr->left;
        } else{
            curr = curr->right;
        }
    }

    if(curr == nullptr){
        cout<<"Energi dengan kode "<<kode<<" tidak ada di organ!\n";
        system("pause");
        return;
    }

    string namaDiambil = curr->nama;

    if(curr->left != nullptr && curr->right != nullptr){
        BST *succParent = curr;
        BST *succ = curr->right;

        while(succ->left != nullptr){
            succParent = succ;
            succ = succ->left;
        }

        curr->kode = succ->kode;
        curr->nama = succ->nama;

        curr = succ;
        parent = succParent;
    }

    BST *anak = (curr->left != nullptr) ? curr->left : curr->right;

    if(parent == nullptr){
        rootOrgan = anak;
    } else if(parent->left == curr){
        parent->left = anak;
    } else {
        parent->right = anak;
    }

    delete curr;
    cout<<"Kode Energi "<<namaDiambil<< " selesai digunakan!\n";
    system("pause");

}

int main(){
    int menu;

    do{
        system("cls");
        cout<<"=== Sistem Organ Inti NIrwana ===\n";
        cout<<"1. Tambah Energi\n";
        cout<<"2. Lihat Energi dalam Antrian\n";
        cout<<"3. Proses Energi\n";
        cout<<"4. Lihat Energi yang Sudah Terserap\n";
        cout<<"5. Hapus RIwayat Energi TEratas\n";
        cout<<"6. Cari Energi di ORgan\n";
        cout<<"7. LIhat Isi Organ\n";
        cout<<"8. Gunakan Energi\n";
        cout<<"9. Keluar\n";
    
        cout<<"Masukkan Pilihan Anda : "; cin>>menu;

        switch (menu)
        {
        case 1:
            /* code */
            tambahEnergi();
            break;
        case 2:
            lihatAntrian();
            break;
        case 3:
            prosesEnergi();
            break;
        case 4:
            lihatEnergiTerserap();
            break;
        case 5:
            hapusEnergiTerserap();
            break;
        case 6:
            cariEnergidiOrgan();
            break;
        case 7:
            lihatOrgan();
            break;
        case 8:
            gunakanEnergi();
            break;
        case 9:
            cout<<"Program Selesai..\n";
            break;
        
        default:
            cout<<"Menu tidak tersedia!\n";
            system("pause");
            break;
        }

    } while(menu != 9);

    return 0;
}