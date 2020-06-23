struct phone { char* manufacturer; int price; };
struct phone examplePhone();
void printPhone(struct phone p);
void modifyPhone(struct phone* p, char* newManufacturer, int newPrice);
