/* strcpy: copy t to s; pointer version 1 */
void strcpy(char *s, char *t)
{
        while ((*s = *t) != '\0') {
                s++;
                t++;
        }

}/* strcpy: copy t to s; pointer version 2 */
void strcpy(char *s, char *t)
{
        while ((*s++ = *t++) != '\0')
                ;
}
