### CLIMBING EXPLORATION WITH C++

> The graph is in the file graphe.txt

> potential error

- Change the "graphe.txt" file path in the main foler

```C++
char nomFe [150] = "/Users/mac/Desktop/Study/myS8/Intelligence Artificielle/PART2/Escalade/Escalade/graphe.txt";
           FILE* fe = fopen (nomFe, "r");
           if (fe == NULL)
           {
               perror (nomFe);
           }
           else
           {
               graphe = lireGraphe (fe, 20);
               fclose (fe);
           }
```
