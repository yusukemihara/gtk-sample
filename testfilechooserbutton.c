#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs glib-2.0 gtk+-3.0 gmodule-2.0` -o $obj $src
$obj
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

G_MODULE_EXPORT void
cb_file_set(
  GtkFileChooserButton *fc,
  GtkTextView *textview)
{
  gchar *file;
  GtkTextBuffer *textbuf;
  gchar *buf;
  gsize size;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc));
  textbuf = gtk_text_view_get_buffer(textview);

  /*テキストファイルを読み込み、テキストビューに表示*/
  if (g_file_get_contents(file,&buf,&size,NULL)) {
    gtk_text_buffer_set_text(textbuf,buf,size);
    g_free(buf);
  }
}

int
main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GObject *window1;
  GObject *entry1;

  gtk_init(&argc,&argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "testfilechooserbutton.ui", NULL);
  gtk_builder_connect_signals(builder, NULL);

  window1 = gtk_builder_get_object(builder, "window1");
  gtk_widget_show_all(GTK_WIDGET(window1));
  gtk_main();

  return 0;
}
