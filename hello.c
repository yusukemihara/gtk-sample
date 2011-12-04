#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

G_MODULE_EXPORT void
cb_activate(
  GtkEntry *entry1,
  GtkLabel *label2) /* hello.uiで指定したオブジェクトlabel2 */
{
  gchar *buf;

  /*ラベルに表示する文字列作成*/
  buf = g_strdup_printf("はろー %s",gtk_entry_get_text(entry1));

  /*ラベルの設定*/
  gtk_label_set_text(label2,buf);
  g_free(buf);
}

int
main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GObject *window1;

  /* Gtkの初期化*/
  gtk_init(&argc,&argv); 

  /* GtkBuilder作成 */
  builder = gtk_builder_new(); 
  /* hello.uiの読み込み*/
  gtk_builder_add_from_file(builder, "hello.ui", NULL); 
  /* hello.uiのシグナルハンドラの設定 */
  gtk_builder_connect_signals(builder, NULL); 

  /* window1のオブジェクト取得 */
  window1 = gtk_builder_get_object(builder, "window1"); 
  /* window1の表示 */
  gtk_widget_show_all(GTK_WIDGET(window1)); 
  /* イベントループ開始 */
  gtk_main(); 

  return 0;
}
