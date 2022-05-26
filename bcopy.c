bcopy(from, to, n)
char *from, *to;
int n;
{
	while(n--) *to++ = *from++;
}

bzero(to, n)
char *to;
int n;
{
	while(n--) *to++ = 0;
}
