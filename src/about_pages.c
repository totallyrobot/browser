#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

char *about_home() {
	FILE *f = fopen("html/browser/home/index.html", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	rewind(f);

	char *string = malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = 0;
	return string;
}

void aboutPagesURISchemeHandler(WebKitURISchemeRequest *request, gpointer user_data) {

    GInputStream *stream;
    gsize         stream_length;
    const gchar  *path;

    path = webkit_uri_scheme_request_get_path (request);
        gchar *contents;

        contents = g_strdup_printf ("<h1>Test</h1>");
        stream_length = strlen (contents);
        stream = g_memory_input_stream_new_from_data (contents, stream_length, g_free);
    webkit_uri_scheme_request_finish (request, stream, stream_length, "text/html");
    g_object_unref (stream);
	printf("h");
}