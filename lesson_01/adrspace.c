/* Vorlagedatei fuer Uebung "Adressraum und Datentypen" */

int a, b;
char c='0';
int d[8]={0x1122, 2, 3, 4, 5, 6, 7, 8};
char *s = "Hallo Welt!";

struct {
   int u;
   char v;
   long w;
} x;



int main ()
{
   int res=0;

   a = 0x8899aabb;
   b = 0xccddeeff;
   c = '1';
   a = d[1];
   x.u = 0x3344;
   x.v = '2';
   x.w = 0x55667788;
   res = sizeof(a);
   res = sizeof(x);
   res = sizeof(s);
   res = sizeof(*s);
   res = sizeof("Hallo Welt!");
   return 0;
}

