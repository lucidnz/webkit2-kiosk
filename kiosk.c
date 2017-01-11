#include <err.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#define URI "file:///var/www/kiosk/index.html"
#define URIMAXLEN 128

void usage(char **);
void destroymainwindow(GtkWidget *, gpointer);
void closewebview(WebKitWebView *, gpointer);

int
main(int argc, char **argv)
{
	GtkWidget *mainwindow;
	GtkWidget *webview;
	char *uri;

	if (argc > 2)
		usage(argv);

	uri = malloc(URIMAXLEN);
	if (!uri)
		err(128, NULL);
	uri = strncpy(uri, argc < 2 ? URI : argv[1], URIMAXLEN);

	gtk_init(&argc, &argv);

	mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	webview = webkit_web_view_new();

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), uri); // start rendering early

	gtk_container_add(GTK_CONTAINER(mainwindow), webview);
	gtk_widget_show_all(mainwindow);
	gtk_window_fullscreen(GTK_WINDOW(mainwindow));

	g_signal_connect(mainwindow, "destroy", G_CALLBACK(destroymainwindow), NULL);
	g_signal_connect(webview, "close", G_CALLBACK(closewebview), mainwindow);

	gtk_main();

	return 0;
}

void
usage(char **argv)
{
	fprintf(stderr, "usage: %s [uri]\n", basename(argv[0]));
	exit(1);
}

void
destroymainwindow(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void
closewebview(WebKitWebView *webview, gpointer window)
{
	gtk_widget_destroy(GTK_WIDGET(window));
}
