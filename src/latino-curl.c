/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <curl/curl.h>
#include <stdlib.h>

#ifdef _WIN32
#define LATINO_BUILD_AS_DLL
#endif

#define LATINO_LIB

#include <latino.h>

#define LIB_CURL_NAME "curl"

struct string {
  char *ptr;
  size_t len;
};

static void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  s->ptr[0] = '\0';
}

static size_t curl_writefunc(void *ptr, size_t size, size_t nmemb,
                             struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size * nmemb;
}

static void curl_peticion(lat_mv *mv) {
  lat_objeto *tiempo = latC_desapilar(mv);
  lat_objeto *o = latC_desapilar(mv);
  lat_objeto *tmp = NULL;
  int espera;
  if (tiempo->tipo != T_NULL) {
    espera = latC_checar_numerico(mv, tiempo);
  }
  char *url = latC_checar_cadena(mv, o);
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    if (espera) {
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, espera);
    };
    res = curl_easy_perform(curl);
    if (res == CURLE_OPERATION_TIMEDOUT) {
      latC_apilar(mv, latO_falso);
      return;
    } else if (res != CURLE_OK) {
      curl_easy_cleanup(curl);
      latC_apilar(mv, latO_nulo);
      return;
    }
    tmp = latC_crear_cadena(mv, s.ptr);
    curl_easy_cleanup(curl);
  }
  latC_apilar(mv, tmp);
}

static void curl_lat_escape(lat_mv *mv) {
  lat_objeto *a = latC_desapilar(mv);
  CURL *curl = curl_easy_init();
  char *texto = latC_checar_cadena(mv, a);
  if (curl && strlen(texto) > 0) {
    char *output = curl_easy_escape(curl, texto, strlen(texto));
    if (output) {
      lat_objeto *tmp = latC_crear_cadena(mv, output);
      latC_apilar(mv, tmp);
      curl_free(output);
    }
  } else {
    latC_error(mv, "Se esperaba una cadena mayor");
  }
}

static size_t escribir_datos(void *ptr, size_t size, size_t nmemb,
                             FILE *stream) {
  size_t cdato = fwrite(ptr, size, nmemb, stream);
  return cdato;
}

static void curl_descargar(lat_mv *mv) {
  lat_objeto *nombre_archivo = latC_desapilar(mv);
  lat_objeto *url = latC_desapilar(mv);
  CURL *curl;
  FILE *fp;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    fp = fopen(latC_checar_cadena(mv, nombre_archivo), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, latC_checar_cadena(mv, url));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, escribir_datos);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      latC_apilar(mv, latO_falso);
      curl_easy_cleanup(curl);
      return;
    }
    latC_apilar(mv, latO_verdadero);
    curl_easy_cleanup(curl);
    fclose(fp);
  }
}
static const lat_CReg libcurl[] = {{"peticion", curl_peticion, 2},
                                   {"escape", curl_lat_escape, 1},
                                   {"descargar", curl_descargar, 2},
                                   {NULL, NULL}};

void latC_abrir_liblatino_curl(lat_mv *mv) {
  latC_abrir_liblatino(mv, LIB_CURL_NAME, libcurl);
}
