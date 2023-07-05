#include <stdio.h>
#include <gtk/gtk.h>
#include "dbase.h"

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show (window);
}



int main(void) {

   GtkApplication *app;
   int status;

   app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
   status = g_application_run (G_APPLICATION (app), NULL, NULL);

   createConnection("testikus");

   queryConnection("SELECT * FROM cars");

   MYSQL_RES* result = queryDB("SELECT * FROM cars");

   int num_fields = mysql_num_fields(result);

   MYSQL_ROW row;

   while ((row = mysql_fetch_row(result)))
   {
         for(int i = 0; i < num_fields; i++)
         {
            printf("%s ", row[i] ? row[i] : "NULL");
         }

         printf("\n");
   }

   mysql_free_result(result);

   closeConnection();

   
   g_object_unref (app);
   return 0;
}