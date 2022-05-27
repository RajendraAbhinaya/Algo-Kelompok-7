#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

//TUGAS-TUGAS
//Linked List (Alexa)
//Read/Write Database (Abhi)
//Sort   (yuda)
//Search (yuda)
//Graph (Abhi)
//Queue (Abhi)
//ASCII Art (Alexa)
//Time.h (Abhi)

typedef struct Queue{
  int lokasi;

  struct Queue *next;
}Queue;

typedef struct Kereta{
  char nama[10];
  int lokasi;
  int kapasitas;
  int harga;
  int queueSize;
  long time;
  int distance;

  struct Kereta *next;
  struct Queue *head, *tail;
}Kereta;

typedef struct Perjalanan{
  char nama[10];
  char lokasi1[16];
  char lokasi2[16];
  int penumpang;
  int kapasitas;
  long awal;
  long akhir;
  int queueSize;

  struct Queue *head, *tail;
  struct Perjalanan *next;
}Perjalanan;

void Continue()
{
  printf("\nPress any key to continue");
  getchar();
}

void swap(struct Kereta *a, struct Kereta *b)
{
    struct Kereta temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int ascendingPartition(struct Kereta *arr, int l, int r)
{
    int pivot = arr[r].kapasitas;
    int i = l-1;

    for(int j=l; j<=r-1; j++)
    {
        if(arr[j].kapasitas <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[r]);
    return(i+1);
}

int descendingPartition(struct Kereta *arr, int l, int r)
{
    int pivot = arr[r].kapasitas;
    int i = l-1;

    for(int j=l; j<=r-1; j++)
    {
        if(arr[j].kapasitas >= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[r]);
    return(i+1);
}

void quickSort(struct Kereta *arr, int l, int r, int ascending, int descending)
{
    if(l<r)
    {
        if(ascending == 1)
        {
            int pi = ascendingPartition(arr, l, r);
            quickSort(arr, l, pi-1, ascending, descending);
            quickSort(arr, pi+1, r, ascending, descending);
        }
        else if(descending == 1)
        {
            int pi = descendingPartition(arr, l, r);
            quickSort(arr, l, pi-1, ascending, descending);
            quickSort(arr, pi+1, r, ascending, descending);
        }
    }
}

void lokasi(int lokasi, char* lokasiString)
{
  int lokasiNum;

  FILE *fileLokasi = fopen("lokasi.txt", "r");
  while(!feof(fileLokasi))
  {
    fscanf(fileLokasi, "%d.%[^\n]\n", &lokasiNum, lokasiString);
    if(lokasiNum == lokasi)
    {
        break;
    }
  }
  fclose(fileLokasi);
}

void printLokasi()
{
  int i, j, k;
  char lokasi1[16], lokasi2[16], lokasi3[16];
  i = 1;
  j = 15;
  k = 29;
  printf("----------------------------------------------------------------\n");
  while(i <= 14)
  {
    lokasi(i, lokasi1);
    lokasi(j, lokasi2);
    lokasi(k, lokasi3);
    printf("%2d. %-16s %2d. %-16s %2d. %-16s\n", i, lokasi1, j, lokasi2, k, lokasi3);
    i++;
    j++;
    k++;
  }
  printf("----------------------------------------------------------------\n");
}

int listKereta(int graph[43][43], struct Kereta *head, struct Kereta *tail, int size)
{
  int choice;
  int i;
  int j;
  int found;
  char lokasiString1[16], lokasiString2[16], searchNama[10];
  time_t currTime;
  Kereta *curr, *node, *temp, *array;
  curr = node = temp = array = NULL;
  Queue *tempQueue, *currQueue;
  tempQueue = currQueue = NULL;
  while(1)
  {
    currTime = time(NULL);
    i = 1;
    curr = head;
    system("cls");
    printf("===================================================================\n");
    printf("| No. |  Nama   |           Lokasi          | Kapasitas |  Harga  |\n");
    printf("===================================================================\n");
    while(curr != NULL)
    {
        if(curr->queueSize == 0)
        {
            lokasi(curr->lokasi, lokasiString1);
            printf("| %-3d | %-7s | %-25s | %-9d | Rp%-5d |\n", i, curr->nama, lokasiString1, curr->kapasitas, curr->harga);
            curr = curr->next;
            i++;
        }
        else
        {
            currQueue = curr->head;
            while(1)
            {
                if(currTime > (curr->time + (graph[curr->head->lokasi][curr->head->next->lokasi] * 60)))
                {
                    tempQueue = curr->head;
                    curr->head = curr->head->next;
                    curr->lokasi = curr->head->lokasi;
                    tempQueue->next = NULL;
                    free(tempQueue);
                    curr->queueSize--;

                    if(curr->head == curr->tail)
                    {
                        curr->head = NULL;
                        curr->tail = NULL;
                        curr->queueSize = 0;
                        lokasi(curr->lokasi, lokasiString1);
                        printf("| %-3d | %-7s | %-25s | %-9d | Rp%-5d |\n", i, curr->nama, lokasiString1, curr->kapasitas, curr->harga);
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            if(curr->queueSize != 0)
            {
                lokasi(curr->head->lokasi, lokasiString1);
                lokasi(curr->head->next->lokasi, lokasiString2);
                strcat(lokasiString1, "->");
                strcat(lokasiString1, lokasiString2);
                printf("| %-3d | %-7s | %-25s | %-9d | Rp%-5d |\n", i, curr->nama, lokasiString1, curr->kapasitas, curr->harga);
            }
            i++;
            curr = curr->next;
        }
    }
    printf("===================================================================\n\n");
    printf("1. Tambahkan Kereta\n");
    printf("2. Hapus Kereta\n");
    printf("3. Sort\n");
    printf("4. Search\n");
    printf("5. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();
    printf("\n");

    if(choice == 1)
    {
      curr = head;
      node = (struct Kereta*)malloc(sizeof(struct Kereta));
      printLokasi();
      printf("\nNama: ");
      gets(node->nama);
      for(i=0; i<size; i++)
      {
          j = strcmp(node->nama, curr->nama);
          curr = curr->next;
          if(j == 0)
          {
            break;
          }
      }
      if(j == 0)
      {
        printf("Nama ini sudah digunakan\n");
      }
      else
      {
        printf("Lokasi(Masukan Nomor): ");
        scanf("%d", &node->lokasi);
        printf("Kapasitas: ");
        scanf("%d", &node->kapasitas);
        printf("Harga: ");
        scanf("%d", &node->harga);
        node->queueSize = 0;

        if(head == NULL)
        {
          head = tail = node;
        }
        else
        {
          tail->next = node;
          tail = tail->next;
        }

        FILE *addDatabase = fopen("database.txt", "a");
        fprintf(addDatabase, "%s#%d#%d#%d#%d\n", node->nama, node->lokasi, node->kapasitas, node->harga, node->queueSize);
        fclose(addDatabase);
        size++;
      }
    }
    else if(choice == 2)
    {
      printf("Hapus Kereta(1-%d): ", size);
      scanf("%d", &choice);
      if(choice > size || choice < 1)
      {
        printf("Invalid Input\n");
      }
      else
      {
        i = 1;
        curr = head;
        while(i != (choice - 1))
        {
          curr = curr->next;
          i++;
        }
        temp = curr->next;
        curr->next = temp->next;
        temp->next = NULL;
        free(temp);
        curr = head;
        FILE *printDatabase = fopen("database.txt", "w");
        while(curr != NULL)
        {
          fprintf(printDatabase, "%s#%d#%d#%d#%d\n", curr->nama, curr->lokasi, curr->kapasitas, curr->harga, curr->queueSize);
          if(curr->queueSize == 0)
          {
            fprintf(printDatabase, "\n");
          }
          else
          {
            fprintf(printDatabase, "#%ld", curr->time);
            currQueue = curr->head;
            while(currQueue != NULL)
            {
                if(currQueue->lokasi > 42)
                {
                    break;
                }
              fprintf(printDatabase, "#%d", currQueue->lokasi);
              currQueue = currQueue->next;
            }
            fprintf(printDatabase, "\n");
          }
          curr = curr->next;
        }
        fclose(printDatabase);
        size--;
      }
    }
    else if(choice == 3)
    {
        printf("\n1.Ascending\n");
        printf("2.Descending\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        array = (struct Kereta*)malloc(sizeof(struct Kereta) * size);
        curr = head;
        for(i=0; i<size; i++)
        {
            strcpy(array[i].nama, curr->nama);
            array[i].lokasi = curr->lokasi;
            array[i].kapasitas = curr->kapasitas;
            array[i].harga = curr->harga;
            curr = curr->next;
        }
        if(choice == 1)
        {
            quickSort(array, 0, size-1, 1, 0);
        }
        else
        {
            quickSort(array, 0, size-1, 0, 1);
        }
        printf("===================================================================\n");
        printf("| No. |  Nama   |           Lokasi          | Kapasitas |  Harga  |\n");
        printf("===================================================================\n");
        for(i=0; i<size; i++)
        {
            lokasi(array[i].lokasi, lokasiString1);
            printf("| %-3d | %-7s | %-25s | %-9d | Rp%-5d |\n", i+1, array[i].nama, lokasiString1, array[i].kapasitas, array[i].harga);
        }
        printf("===================================================================\n");
        Continue();
    }
    else if(choice == 4)
    {
        printf("Search nama: ");
        gets(searchNama);
        curr = head;
        found = 0;
        while(curr != NULL)
        {
            if(strcmp(curr->nama, searchNama) == 0)
            {
                printf("================================\n");
                printf("Nama: %s\n", curr->nama);
                lokasi(curr->lokasi, lokasiString1);
                printf("Lokasi: %s\n", lokasiString1);
                printf("Kapasitas: %d\n", curr->kapasitas);
                printf("Harga: Rp%d\n", curr->harga);
                printf("================================\n");
                found = 1;
            }
            curr = curr->next;
        }
        if(found == 0)
        {
            printf("Kereta tidak ditemukan\n");
        }
        Continue();
    }
    else
    {
        FILE *printDatabase2 = fopen("database.txt", "w");
        curr = head;
        while(curr != NULL)
        {
          fprintf(printDatabase2, "%s#%d#%d#%d#%d", curr->nama, curr->lokasi, curr->kapasitas, curr->harga, curr->queueSize);
          if(curr->queueSize == 0)
          {
            fprintf(printDatabase2, "\n");
          }
          else
          {
            fprintf(printDatabase2, "#%ld", curr->time);
            currQueue = curr->head;
            while(currQueue != NULL)
            {
                if(currQueue->lokasi > 42)
                {
                    break;
                }
              fprintf(printDatabase2, "#%d", currQueue->lokasi);
              currQueue = currQueue->next;
            }
            fprintf(printDatabase2, "\n");
          }
          curr = curr->next;
        }
        fclose(printDatabase2);
        return size;
    }
  }
}

int djikstraKereta(int graph[43][43], int start, int end)
{
  int cost[43][43], distance[43], pred[43];
  int visited[43], count, mindistance, nextnode, i, j;

  for (i = 0; i < 43; i++)
  {
      for (j = 0; j < 43; j++)
      {
          if (graph[i][j] == 0)
          {
              cost[i][j] = 9999;
          }
          else
          {
              cost[i][j] = graph[i][j];
          }
      }
  }
  for (i = 0; i < 43; i++)
  {
      distance[i] = cost[end][i];
      pred[i] = end;
      visited[i] = 0;
  }
  distance[end] = 0;
  visited[end] = 1;
  count = 1;
  while (count < 42)
  {
      mindistance = 9999;
      for (i = 0; i < 43; i++)
      {
          if (distance[i] < mindistance && !visited[i])
          {
              mindistance = distance[i];
              nextnode = i;
          }
      }
      visited[nextnode] = 1;
      for (i = 0; i < 43; i++)
      {
          if (!visited[i])
          {
              if (mindistance + cost[nextnode][i] < distance[i])
              {
                  distance[i] = mindistance + cost[nextnode][i];
                  pred[i] = nextnode;
              }
          }
      }
      count++;
  }
  return(distance[start]);
}

void perjalananKereta(int graph[43][43], struct Kereta *headKereta, int size)
{
  char lokasiString1[16], lokasiString2[16];
  int cost[43][43], distance[43], pred[43];
  int visited[43], count, mindistance, nextnode, i, j;
  int start, end;
  int queueSize;
  int input;
  int penumpang;
  int jarak1, jarak2;
  time_t awal, akhir;
  Queue *node, *head, *tail, *curr;
  node = head = tail = curr = NULL;
  Kereta *currKereta;
  currKereta = NULL;

  printLokasi();
  printf("Lokasi Awal: ");
  scanf("%d", &start);
  printf("Lokasi Akhir: ");
  scanf("%d", &end);

  currKereta = headKereta;
  i = 1;
  printf("\n=====================================================================\n");
  printf("| No. |  Nama   |      Lokasi     | Kapasitas |  Harga  | Jarak(km) |\n");
  printf("=====================================================================\n");
  while(currKereta != NULL)
  {
    if(currKereta->queueSize == 0)
    {
      currKereta->distance = djikstraKereta(graph, currKereta->lokasi, start);
      lokasi(currKereta->lokasi, lokasiString1);
      printf("| %-3d | %-7s | %-15s | %-9d | Rp%-5d | %-9d |\n", i, currKereta->nama, lokasiString1, currKereta->kapasitas, currKereta->harga, currKereta->distance);
    }
      currKereta = currKereta->next;
      i++;
  }
  printf("=====================================================================\n");

  while(1)
  {
    printf("Pilihan: ");
    scanf("%d", &input);
    if(input > size || input < 1)
    {
      printf("Invalid Input\n");
    }
    else
    {
      break;
    }
  }
  currKereta = headKereta;
  i = 1;
  while(i != input)
  {
    currKereta = currKereta->next;
    i++;
  }
  while(1)
  {
    printf("Jumlah Penumpang(1-%d): ",currKereta->kapasitas);
    scanf("%d", &penumpang);
    if(penumpang > currKereta->kapasitas || penumpang < 1)
    {
      printf("Invalid Input\n");
    }
    else
    {
      break;
    }
  }

  for (i = 0; i < 43; i++)
  {
      for (j = 0; j < 43; j++)
      {
          if (graph[i][j] == 0)
          {
              cost[i][j] = 9999;
          }
          else
          {
              cost[i][j] = graph[i][j];
          }
      }
  }
  for (i = 0; i < 43; i++)
  {
      distance[i] = cost[start][i];
      pred[i] = start;
      visited[i] = 0;
  }
  distance[start] = 0;
  visited[start] = 1;
  count = 1;
  while (count < 42)
  {
      mindistance = 9999;
      for (i = 0; i < 43; i++)
      {
          if (distance[i] < mindistance && !visited[i])
          {
              mindistance = distance[i];
              nextnode = i;
          }
      }
      visited[nextnode] = 1;
      for (i = 0; i < 43; i++)
      {
          if (!visited[i])
          {
              if (mindistance + cost[nextnode][i] < distance[i])
              {
                  distance[i] = mindistance + cost[nextnode][i];
                  pred[i] = nextnode;
              }
          }
      }
      count++;
  }

  if (i != start)
  {
      jarak1 = distance[currKereta->lokasi];
      node = (struct Queue*) malloc(sizeof(struct Queue));
      node->lokasi = currKereta->lokasi;
      node->next = NULL;
      head = node;
      tail = node;
      j = currKereta->lokasi;
      queueSize = 1;
      do {
          j = pred[j];
          queueSize++;
          node = (struct Queue*) malloc(sizeof(struct Queue));
          node->lokasi = j;
          node->next = NULL;
          tail->next = node;
          tail = tail->next;
      } while (j != start);
  }

  for (i = 0; i < 43; i++)
  {
      for (j = 0; j < 43; j++)
      {
          if (graph[i][j] == 0)
          {
              cost[i][j] = 9999;
          }
          else
          {
              cost[i][j] = graph[i][j];
          }
      }
  }
  for (i = 0; i < 43; i++)
  {
      distance[i] = cost[end][i];
      pred[i] = end;
      visited[i] = 0;
  }
  distance[end] = 0;
  visited[end] = 1;
  count = 1;
  while (count < 42)
  {
      mindistance = 9999;
      for (i = 0; i < 43; i++)
      {
          if (distance[i] < mindistance && !visited[i])
          {
              mindistance = distance[i];
              nextnode = i;
          }
      }
      visited[nextnode] = 1;
      for (i = 0; i < 43; i++)
      {
          if (!visited[i])
          {
              if (mindistance + cost[nextnode][i] < distance[i])
              {
                  distance[i] = mindistance + cost[nextnode][i];
                  pred[i] = nextnode;
              }
          }
      }
      count++;
  }
  if (i != end)
  {
      queueSize++;
      jarak2 = distance[start];
      node = (struct Queue*) malloc(sizeof(struct Queue));
      node->lokasi = start;
      node->next = NULL;
      tail->next = node;
      tail = tail->next;
      j = start;
      do {
          j = pred[j];
          queueSize++;
          node = (struct Queue*) malloc(sizeof(struct Queue));
          node->lokasi = j;
          node->next = NULL;
          tail->next = node;
          tail = tail->next;
      } while (j != end);
  }
  curr = head;
  while(curr!= NULL)
  {
      lokasi(curr->lokasi, lokasiString1);
      printf("%s->", lokasiString1);
      curr = curr->next;
  }

  awal = time(NULL);
  akhir = time(NULL);
  awal += jarak1 * 60;
  akhir += (jarak1 + jarak2) * 60;

  currKereta->head = head;
  currKereta->tail = tail;
  currKereta->queueSize = queueSize;
  awal = time(NULL);
  currKereta->time = awal;

  FILE *printPerjalanan = fopen("perjalanan.txt", "a");
  fprintf(printPerjalanan, "%s#%s#%s#%d#%d#%ld#%ld#", currKereta->nama, lokasiString1, lokasiString2, penumpang, currKereta->kapasitas, awal, akhir);
  curr = currKereta->head;
  while(curr != NULL)
  {
      if(curr->lokasi > 42)
      {
          break;
      }
      fprintf(printPerjalanan, "#%d", curr->lokasi);
      curr = curr->next;
  }
  fprintf(printPerjalanan, "\n");
  fclose(printPerjalanan);

  currKereta = headKereta;
  FILE *printDatabase3 = fopen("database.txt", "w");
  while(currKereta != NULL)
  {
    fprintf(printDatabase3, "%s#%d#%d#%d#%d", currKereta->nama, currKereta->lokasi, currKereta->kapasitas, currKereta->harga, currKereta->queueSize);
    if(currKereta->queueSize == 0)
    {
      fprintf(printDatabase3, "\n");
    }
    else
    {
      fprintf(printDatabase3, "#%ld", currKereta->time);
      curr = currKereta->head;
      while(curr != NULL)
      {
          if(curr->lokasi > 42)
          {
              break;
          }
          fprintf(printDatabase3, "#%d", curr->lokasi);
          curr = curr->next;
      }
      fprintf(printDatabase3, "\n");
    }
    currKereta = currKereta->next;
  }
  fclose(printDatabase3);
  getchar();
  Continue();
}


void statusPerjalanan()
{
    time_t currTime;

    Perjalanan *head, *tail, *node, *curr;
    Queue *headQueue, *tailQueue, *nodeQueue, *tempQueue;
    head = tail = node = curr = NULL;
    headQueue = tailQueue = nodeQueue = tempQueue = NULL;

    currTime = time(NULL);

    FILE *readPerjalanan = fopen("perjalanan.txt", "r");
    while(!feof(readPerjalanan))
    {
        node = (struct Perjalanan*) malloc(sizeof(struct Perjalanan));
        fscanf(readPerjalanan, "%[^#]#%[^#]#%[^#]#%d#%d#%ld#%ld\n", node->nama, node->lokasi1, node->lokasi2, &node->penumpang, &node->kapasitas, &node->awal, &node->akhir);
        node->next = NULL;
        if(node->akhir < currTime)
        {
            FILE *printHistory = fopen("history.txt", "a");
            fprintf(printHistory, "%s#%s#%s#%d#%d#%ld#%ld\n", node->nama, node->lokasi1, node->lokasi2, node->penumpang, node->kapasitas, node->awal, node->akhir);
            fclose(printHistory);
        }
        else if(head == NULL)
        {
          head = tail = node;
        }
        else
        {
          tail->next = node;
          tail = tail->next;
        }
    }
    fclose(readPerjalanan);

    if(head == NULL)
    {
        printf("Sedang tidak ada perjalanan\n");
    }
    else
    {
        curr = head;
        while(curr != NULL)
        {
            printf("==========================================\n");
            printf("Kereta         : %s\n", curr->nama);
            printf("Penumpang      : %d/%d\n", curr->penumpang, curr->kapasitas);
            printf("Lokasi Awal    : %s\n", curr->lokasi1);
            printf("Lokasi Akhir   : %s\n", curr->lokasi2);
            printf("Waktu Berangkat: %s", ctime(&curr->awal));
            printf("Waktu Selesai  : %s", ctime(&curr->akhir));
            printf("==========================================\n");
            curr = curr->next;
        }
    }
    Continue();
}

void sejarah()
{
    Perjalanan *head, *tail, *node, *curr;
    Queue *headQueue, *tailQueue, *nodeQueue, *tempQueue;
    head = tail = node = curr = NULL;
    headQueue = tailQueue = nodeQueue = tempQueue = NULL;

    FILE *readSejarah = fopen("history.txt", "r");
    while(!feof(readSejarah))
    {
        node = (struct Perjalanan*) malloc(sizeof(struct Perjalanan));
        fscanf(readSejarah, "%[^#]#%[^#]#%[^#]#%d#%d#%ld#%ld\n", node->nama, node->lokasi1, node->lokasi2, &node->penumpang, &node->kapasitas, &node->awal, &node->akhir);
        node->next = NULL;
        if(head == NULL)
        {
          head = tail = node;
        }
        else
        {
          tail->next = node;
          tail = tail->next;
        }
    }
    fclose(readSejarah);

    if(head == NULL)
    {
        printf("Sedang tidak ada perjalanan\n");
    }
    else
    {
        curr = head;
        while(curr != NULL)
        {
            printf("==========================================\n");
            printf("Kereta         : %s\n", curr->nama);
            printf("Penumpang      : %d/%d\n", curr->penumpang, curr->kapasitas);
            printf("Lokasi Awal    : %s\n", curr->lokasi1);
            printf("Lokasi Akhir   : %s\n", curr->lokasi2);
            printf("Waktu Berangkat: %s", ctime(&curr->awal));
            printf("Waktu Selesai  : %s", ctime(&curr->akhir));
            printf("==========================================\n");
            curr = curr->next;
        }
    }
    Continue();
}


int main() // menu utama
{
  int choice;
  int size = 0;
  int i;
  time_t Time;
  Kereta *head, *tail, *node;
  Queue *headQueue, *tailQueue, *nodeQueue, *curr;

  head = tail = node = NULL;
  headQueue = tailQueue = nodeQueue = NULL;

  FILE *fileDatabase = fopen("database.txt", "r");
  while(!feof(fileDatabase))
  {
    node = (struct Kereta*)malloc(sizeof(struct Kereta));
    fscanf(fileDatabase, "%[^#]#%d#%d#%d#%d", node->nama, &node->lokasi, &node->kapasitas, &node->harga, &node->queueSize);
    if(node->queueSize == 0)
    {
      node->head == NULL;
      node->tail == NULL;
      fscanf(fileDatabase, "\n");
    }
    else
    {
      headQueue = tailQueue = nodeQueue = NULL;
      fscanf(fileDatabase, "#%ld", &node->time);
      for(i=0; i<node->queueSize; i++)
      {
        nodeQueue = (struct Queue*) malloc(sizeof(struct Queue));
        fscanf(fileDatabase, "#%d", &nodeQueue->lokasi);
        if(headQueue == NULL)
        {
          headQueue = tailQueue = nodeQueue;
        }
        else
        {
          tailQueue->next = nodeQueue;
          tailQueue = tailQueue->next;
        }
      }
      node->head = headQueue;
      node->tail = tailQueue;
      fscanf(fileDatabase, "\n");
    }

    node->next = NULL;
    if(head == NULL)
    {
      head = tail = node;
    }
    else
    {
      tail->next = node;
      tail = tail->next;
    }
    size++;
  }
  fclose(fileDatabase);

  //                    0               5              10               15                20              25                30              35              40
    int graph[43][43] = {{0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,33,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,33,0 ,45 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,45,0  ,106,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,106,0  ,35,28,0 ,0 ,0  ,28,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,35 ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,28 ,0 ,0 ,29,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,29,0 ,78,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,78,0 ,32 ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,32,0  ,0 ,108,57,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,28 ,0 ,0 ,0 ,0 ,0  ,0 ,59 ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,108,59,0  ,72,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,57 ,0 ,72 ,0 ,14 ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,14,0  ,0 ,116,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,116,0 ,0  ,44 ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,44 ,0  ,110,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,110,0  ,0 ,0 ,31,42,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,80,0  ,0  ,0  ,0 ,42,0 ,0 ,0 ,0 ,0  ,79 ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,86,0  ,0  ,0  ,42,0 ,60,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,31 ,0 ,60,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,42 ,0 ,0 ,0 ,0 ,45,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,45,0 ,72,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,72,0 ,65 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,65,0  ,0  ,104,130,0 ,0 ,0 ,90,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,79,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,104,98 ,0  ,222,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,130,0  ,222,0  ,40,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,40 ,0 ,68,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,68,0 ,47,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,47,0 ,0 ,0 ,89,0  ,0 ,0 ,0 ,52,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,90 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,57,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,57,0 ,51,50 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,89,0 ,51,0 ,37 ,0 ,0 ,0 ,76,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,50,37,0  ,53,0 ,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,53 ,0 ,30,0 ,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,30,0 ,79,0 ,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,79,0 ,37,0  ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,52,54,0 ,76,0  ,0 ,0 ,37,0 ,60 ,0 ,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,60,0  ,87,0 ,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,87 ,0 ,56,0 },
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,56,0 ,58},
                     {0,0 ,0 ,0  ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,0  ,0 ,0  ,0 ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0  ,0  ,0  ,0 ,0 ,0 ,0 ,0 ,0 ,0  ,0 ,0 ,0 ,0 ,0  ,0 ,58,0 } };
    //                    0               5              10               15                20              25                30              35              40


  while(1)
  {
    system("cls");

    Time = time(NULL);
    printf("%s", ctime(&Time));

    printf("1. List Kereta\n");
    printf("2. Atur Perjalanan Kereta\n");
    printf("3. Status Perjalanan Kereta\n");
    printf("4. Sejarah Perjalanan Kereta\n");
    printf("5. Peta Rute Kereta\n");
    printf("6. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();
    system("cls");
    if(choice == 1)//Menu List Kereta
    {
      size = listKereta(graph, head, tail, size);
    }
    else if(choice == 2)//Menu Atur Perjalanan Kereta
    {
      perjalananKereta(graph, head, size);
    }
    else if(choice == 3)//Menu Status Perjalanan
    {
      statusPerjalanan();
    }
    else if(choice == 4)//Menu Sejarah Perjalanan
    {
      sejarah();
    }
    else if(choice == 5)//Peta Rute Kereta
    {
      printf("  ____________________________________________________________________________________________________\n\n");
      printf("                                PETA RUTE KERETA: JAVA RAIL NETWORK\n");
      printf("                                -----------------------------------\n\n");
      printf("      * A = Stasiun awal / stasiun akhir\n");
      printf("      * T = Stasiun yang tersedia untuk transit\n");
      printf("\n");
      printf("  ____________________________________________________________________________________________________\n");
      printf("\n\n");
      printf("    Merak      Serang   Rangkasbitung  Jakarta\n");
      printf("      o-----------o-----------o-----------o\n");
      printf("      A                                   T\n");
      printf("\n");
      printf("   Jakarta    Tangerang\n");
      printf("      o-----------o\n");
      printf("      T           A\n");
      printf("\n");
      printf("   Jakarta     Bekasi     Cikampek\n");
      printf("      o-----------o-----------o\n");
      printf("      T                       T\n");
      printf("\n");
      printf("   Jakarta      Depok       Bogor     Sukabumi     Cianjur     Cimahi\n");
      printf("      o-----------o-----------o-----------o-----------o-----------o\n");
      printf("      T                                                           T\n");
      printf("\n");
      printf("   Cikampek    Cirebon      Tegal\n");
      printf("      o-----------o-----------o\n");
      printf("      T                       T\n");
      printf("\n");
      printf("   Cikampek    Cirebon      Prupuk\n");
      printf("      o-----------o-----------o\n");
      printf("      T                       T\n");
      printf("\n");
      printf("   Cikampek    Cimahi\n");
      printf("      o-----------o\n");
      printf("      T           T\n");
      printf("\n");
      printf("   Cimahi      Bandung   Tasikmalaya   Banjar       Kroya\n");
      printf("      o-----------o-----------o-----------o-----------o\n");
      printf("      T                                               T\n");
      printf("\n");
      printf("    Tegal    Pekalongan   Semarang      Cepu     Bojonegoro   Lamongan     Surabaya\n");
      printf("      o-----------o-----------o-----------o-----------o-----------o-----------o\n");
      printf("      T                                                                       T\n");
      printf("\n");
      printf("    Tegal      Prupuk\n");
      printf("      o-----------o\n");
      printf("      T           T\n");
      printf("\n");
      printf("   Prupuk     Purwokerto    Kroya\n");
      printf("      o-----------o-----------o\n");
      printf("      T                       T\n");
      printf("\n");
      printf("    Kroya    Karanganyar   Kutoarjo  Yogyakarta  Solobalapan\n");
      printf("      o-----------o-----------o-----------o-----------o\n");
      printf("      T                                               T\n");
      printf("\n");
      printf("   Surabaya    Jombang\n");
      printf("      o-----------o\n");
      printf("      T           T\n");
      printf("\n");
      printf("   Surabaya    Bangil\n");
      printf("      o-----------o\n");
      printf("      T           T\n");
      printf("\n");
      printf(" Solobalapan    Paron      Nganjuk     Jombang\n");
      printf("      o-----------o-----------o-----------o\n");
      printf("      T                                   T\n");
      printf("\n");
      printf("   Jombang     Kediri    Tulungagung   Blitar      Malang      Bangil\n");
      printf("      o-----------o-----------o-----------o-----------o-----------o\n");
      printf("      T                                                           T\n");
      printf("\n");
      printf("   Bangil    Probolinggo  Rambipuji    Kalibaru  Banyuwangi\n");
      printf("      o-----------o-----------o-----------o-----------o\n");
      printf("      T                                               A\n");
      printf("\n");
      printf("  ____________________________________________________________________________________________________\n");printf("\n");
      printf("Tekan apapun untuk kembali ke menu utama.\n");
      getchar();
    }
    else//Exit
    {
      return 0;
    }
  }
}
