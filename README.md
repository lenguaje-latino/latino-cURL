### latino-curl
Libreria dinamica para uso de curl en [latino](https://github.com/primitivorm/latino)

##### Uso en codigo latino
```
//necesario para agregar la libreria dinamica
incluir("curl")

//se realiza una peticion a www.telegramforo.com y se muestra contenido
resp = curl.peticion("www.telegramforo.com")
poner(resp)

//se codifica un texto y se realiza una busqueda en google
busqueda = "perros y gatos"
resp = curl.peticion("https://www.google.com.mx/search?q=" .. curl.escape(busqueda))
poner(resp)
```

##### Prerequisitos
Tener instalado [latino](https://github.com/primitivorm/latino)

### Instalacion
##### linux
```
$git clone https://github.com/primitivorm/latino-curl
$cd latino-curl
$git submodule update --init --recursive
$sudo ./instalar.sh
```

##### Dependecias
[curl](https://github.com/curl/curl)

##### Cualquier aportacion o sugerencia es bienvenida
