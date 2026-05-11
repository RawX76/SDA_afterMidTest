#include "nbtree_dynamic.h"

int main() {
Tree pohon;
Create_tree(&pohon);
int menu;

address A = Alokasi('A');
pohon = A; // root = A

address B = Alokasi('B');
address C = Alokasi('C');
address D = Alokasi('D');
address E = Alokasi('E');
address F = Alokasi('F');
address G = Alokasi('G');
address H = Alokasi('H');
address I = Alokasi('I');
address J = Alokasi('J');

AddChild(A, B);
AddChild(A, C);
AddChild(B, D);
AddChild(B, E);
AddChild(C, F);
AddChild(C, G);
AddChild(C, H);
AddChild(E, I);
AddChild(E, J);

    do
    {
    printf("    Non Binary Tree - dinamis\n");
    printf("\n");
    printf(" 1.  Traversal PreOrder\n");
    printf(" 2.  Traversal PostOrder\n");
    printf(" 3.  Traversal InOrder\n");
    printf(" 4.  Traversal Level Order\n");
    printf(" 5.  Print Tree\n");
    printf(" 6.  Search node Tree\n");
    printf(" 7.  Jumlah Daun/Leaf\n");
    printf(" 8.  Mencari Level node Tree\n");
    printf(" 9.  Kedalaman Tree\n");
    printf(" 10. Membandingkan 2 node Tree\n");
    printf(" 11. Exit\n");
    printf("----------------------------------------\n");
    printf("Pilih Menu: ");
    scanf("%d", &menu);

            switch (menu) {
            case 1:
                printf("\n=== Traversal PreOrder ===\n");
                PreOrder(pohon);
                break;
            case 2:
                printf("\n=== Traversal PostOrder ===\n");
                PostOrder(pohon);
                break;
            case 3:
                printf("\n=== Traversal InOrder ===\n");
                InOrder(pohon);
                break;
            case 4:
                printf("\n=== Traversal Level Order ===\n");
                LevelOrder(pohon);
                break;
            case 5:
                PrintTree(pohon);
                break;
            case 6:
                Search(pohon, 'E') ? printf("Node 'E' DITEMUKAN di dalam tree.\n") : printf("Node 'E' TIDAK ditemukan di dalam tree.\n");
                break;
            case 7:
                printf("\n=== Jumlah Daun/Leaf ===\n");
                printf("Jumlah daun (node tanpa anak): %d\n", NbDaun(pohon));
                break;
            case 8:
                printf("\n=== Level Node ===\n");
                printf("Level dari 'E': %d\n", Level(pohon, 'E'));
                break;
            case 9:
                printf("\n=== Kedalaman Tree ===\n");
                printf("Kedalaman (depth) tree: %d\n", Depth(pohon));
                break;
            case 10:
                break;
            case 11:
                printf("\nTerima kasih! Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid (1-11).\n");
        }
        
    } while (menu != 11);
    return 0;
}