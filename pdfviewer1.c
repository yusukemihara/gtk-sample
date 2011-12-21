#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs poppler-glib glib-2.0 gtk+-2.0 gmodule-2.0` -o $obj $src
$obj
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkwindow.h>
#include <poppler.h>

static PopplerDocument *doc = NULL;
/* Gtk2ではobjectが渡せないのでstatic変数を利用 */
static GtkWidget *darea1 = NULL;

static gboolean
render_page(GtkWidget *widget)
{
  /* GtkDrawingAreaにPDFを描画 */

  static cairo_surface_t *surface = NULL;
  cairo_t *cr;
  double width,height;
  PopplerPage *page;
  GdkWindow *window;

  if (doc == NULL) {
    return FALSE;
  }

  if (surface != NULL) {
    cairo_surface_destroy(surface);
    surface = NULL;
  }

  /* PDFの1ページ目を表示する。第2引数を変えればそのページを表示 */
  page = poppler_document_get_page(doc,0);

  /* PDFページのサイズを取得 */
  poppler_page_get_size(page, &width, &height);

  /* DrawingAreaをPDFページのサイズに設定=等倍 */
  gtk_widget_set_size_request(widget,(int)width,(int)height);

  /* cairo surface作成 */
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
    width,height);
  cr = cairo_create(surface);
  cairo_save(cr);
  /* スケールを等倍 */
  cairo_scale(cr,1.0,1.0);
  /* surfaceにページを描画 */
  poppler_page_render(page,cr);
  cairo_restore(cr);

  cairo_set_operator (cr, CAIRO_OPERATOR_DEST_OVER);
  cairo_set_source_rgb (cr, 1., 1., 1.);
  cairo_paint (cr);
  cairo_destroy (cr);

  /* DrawingAreaのGdkWindowを取得 */
  window = gtk_widget_get_window(widget);
  if (window != NULL) {
    /* GdkWindowにsurfaceを設定 */
    cr = gdk_cairo_create(window);
    cairo_set_source_surface(cr,surface,0,0);
    cairo_paint(cr);
    cairo_destroy(cr);
  }

  g_object_unref(page);
}

G_MODULE_EXPORT void
cb_file_set(
  GtkFileChooserButton *fc,
  gpointer data)
{
  gchar *file,*url;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc));
  if (doc != NULL) {
    g_object_unref(doc);
  }
  /* file://ファイルのフルパスとしてURL作成 */
  url = g_strconcat("file://",file,NULL);
  /* poppler documentの作成(PDFファイルの読み込み) */
  doc = poppler_document_new_from_file(url,NULL,NULL);
  g_free(url);
  /* DrawingAreaへ描画 */
  render_page(darea1);
}

/* Gtk3の場合 */
#if 0
G_MODULE_EXPORT gboolean
cb_draw(GtkWidget *widget,
  cairo_t  *cr,
  gpointer data)
{
  return render_page(widget);
}
#else
G_MODULE_EXPORT gboolean
cb_expose(GtkWidget *widget,
  GdkEvent  *event,
  gpointer data)
{
  return render_page(widget);
}
#endif

int
main(int argc, char *argv[])
{
  GtkBuilder *builder;
  GObject *window1;
  GObject *entry1;

  gtk_init(&argc,&argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "pdfviewer1.ui", NULL);
  gtk_builder_connect_signals(builder, NULL);

  window1 = gtk_builder_get_object(builder, "window1");
  darea1 = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea1"));

  gtk_widget_show_all(GTK_WIDGET(window1));
  gtk_main();

  return 0;
}
