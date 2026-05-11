#include "nbtree_dynamic.h"

//modul konstruktor
void Create_tree(Tree *T) {
    *T = NULL; // Inisialisasi tree kosong
}

address Alokasi(infotype X){
    address P = (address)malloc(sizeof(Node));
    if (P != NULL)
    {
        P->info = X;
        P->ps_fs = NULL;
        P->ps_nb = NULL;
        P->ps_pr = NULL;
    }
    return P; // Mengembalikan address node baru atau NULL jika gagal
}

//modul validasi
int IsEmpty(Tree T) {
    if (T == NULL)
    {
        return 1; // Mengembalikan 1 jika kosong
    }
    return 0; // Mengembalikan 0 jika tidak kosong
}

//modul update
void AddChild(address parent, address child){
    if(parent != NULL && child != NULL) {
        child->ps_pr = parent; // Set parent dari child
        if (parent->ps_fs == NULL) {
            parent->ps_fs = child; // Jika parent belum memiliki anak, set child sebagai anak pertama
        } else {
            address sibling = parent->ps_fs;
            while (sibling->ps_nb != NULL) {
                sibling = sibling->ps_nb; // Cari saudara terakhir
            }
            sibling->ps_nb = child; // Tambahkan child sebagai saudara berikutnya
        }
    }
}

//Modul traversal
void PreOrder(Tree node) {
    if (node != NULL) {
        printf("%c ", node->info); // Proses node saat kunjungan
        PreOrder(node->ps_fs); // Kunjungi anak pertama
        PreOrder(node->ps_nb); // Kunjungi saudara berikutnya
    }
}

void PostOrder(Tree node) {
    if (node != NULL) {
        PostOrder(node->ps_fs);      // 1. Selesaikan semua anak/keturunan dulu
        printf("%c ", node->info);   // 2. Baru proses diri sendiri (Root)
        PostOrder(node->ps_nb);      // 3. Lanjut ke saudara berikutnya
    }
}

void InOrder(Tree node) {
    if (node != NULL) {
        if (node->ps_fs != NULL) {
            InOrder(node->ps_fs);    // 1. Kunjungi anak pertama
            printf("%c ", node->info); // 2. Proses diri sendiri (Root)
            
            // 3. Kunjungi sisa anak-anak lainnya (saudara dari anak pertama)
            Tree sibling = node->ps_fs->ps_nb;
            while (sibling != NULL) {
                InOrder(sibling);
                sibling = sibling->ps_nb;
            }
        } else {
            // Jika tidak punya anak, langsung cetak diri sendiri
            printf("%c ", node->info);
        }
    }
}

void LevelOrder(Tree Node) {
    if (Node == NULL)
    {
        return;
    }

    #define MAX_QUEUE_SIZE 100
    address queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = Node; // Enqueue root

        while (front < rear)
        {
            address current = queue[front++]; // Dequeue
            printf("%c ", current->info); // Proses node saat kunjungan

            address child = current->ps_fs; // Mulai dari anak pertama
            while (child != NULL)
            {
                queue[rear++] = child; // Enqueue anak
                child = child->ps_nb; // Lanjut ke saudara berikutnya
        }  
    }
}

//BANTUAN REKURSIF UNTUK PRINT TREE
static void printTreeHelper(address node, int depth) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  "); // Indentasi untuk level
    }
    printf("%c\n", node->info); // Cetak info node
    printTreeHelper(node->ps_fs, depth + 1); // Kunjungi anak pertama
    printTreeHelper(node->ps_nb, depth); // Kunjungi saudara berikutnya
}

void PrintTree(Tree T) {
    printTreeHelper(T, 0); // Mulai dari root dengan depth 0
}

//modul pencarian

int Search(Tree T, infotype X) {
    if (T == NULL) {
        return 0; // Tidak ditemukan
    }
    if (T->info == X) {
        return 1; // Ditemukan
    }
    // Cari di anak pertama
    if (Search(T->ps_fs, X)) {
        return 1; // Ditemukan di anak pertama
    }
    // Cari di saudara berikutnya
    return Search(T->ps_nb, X); // Lanjut ke saudara berikutnya
}

//modul analisis tree

int NbElmt(Tree T) {
    if (T == NULL) {
        return 0; // Tidak ada elemen
    }
    // Hitung elemen di anak pertama dan saudara berikutnya
    return 1 + NbElmt(T->ps_fs) + NbElmt(T->ps_nb); // Hitung node saat kunjungan
}

int NbDaun(Tree T) {
    if (T == NULL) {
        return 0; // Tidak ada daun
    }
    if (T->ps_fs == NULL) {
        return 1 + NbDaun(T->ps_nb); // Node ini adalah daun
    }
    else{
        return NbDaun(T->ps_fs) + NbDaun(T->ps_nb); // Hitung daun di anak pertama dan saudara berikutnya
    }
}

static int LevelHelper(Tree T, infotype X, int current) {
    if (T == NULL) {
        return -1; // Tidak ditemukan
    }
    if (T->info == X) {
        return current; // Ditemukan, kembalikan level
    }
    // Cari di anak pertama
    int found = LevelHelper(T->ps_fs, X, current + 1);
    if (found != -1) {
        return found; // Ditemukan di anak pertama
    }
    // Cari di saudara berikutnya
    return LevelHelper(T->ps_nb, X, current); // Lanjut ke saudara berikutnya
}

int Level(Tree T, infotype X) {
    return LevelHelper(T, X, 0); // Mulai pencarian dari level 0
}

int Max(int a, int b) {
    return (a > b) ? a : b; // Mengembalikan nilai maksimum antara a dan b
}

int Depth(Tree T) {
    if (T == NULL) {
        return 0; // Kedalaman tree kosong
    }

    int max_child_depth = 0;
    address child = T->ps_fs; // Mulai dari anak pertama
    while (child != NULL)
    {
        int child_depth = Depth(child);
        max_child_depth = Max(max_child_depth, child_depth);
        child = child->ps_nb; // Lanjut ke saudara berikutnya
    }
    return max_child_depth + 1; // Tambahkan 1 untuk level saat ini
}

//Modul dealokasi
void DeAlokasi(Tree *T) {
    if (*T != NULL)
    {
        DeAlokasi(&((*T)->ps_fs)); // Dealokasi anak pertama
        DeAlokasi(&((*T)->ps_nb)); // Dealokasi saudara berikutnya
        free(*T); // Dealokasi node saat ini
        *T = NULL; // Set pointer to NULL
    }   
}