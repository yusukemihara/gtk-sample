#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs glib-2.0 gtk+-2.0 gmodule-2.0` -o $obj $src
$obj
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

G_MODULE_EXPORT void
cb_switch_page(
  GtkNotebook *note, /*GtkNotebook is deprecated,in gtk3 GtkWidget *page*/
  GtkNotebookPage *page,
  guint pageno,
  gpointer data)
{
  printf("switch page [%d][%p]\n",pageno,page);
}

int
main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GObject *window1;
  GObject *entry1;

  gtk_init(&argc,&argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "testnotebook.ui", NULL);
  gtk_builder_connect_signals(builder, NULL);

  window1 = gtk_builder_get_object(builder, "window1");
  gtk_widget_show_all(GTK_WIDGET(window1));
  gtk_main();

  return 0;
}
