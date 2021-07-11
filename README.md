### latino-curl
Librería dinámica para uso de curl en [latino](https://github.com/primitivorm/latino)

##### Prerequisitos
Tener instalado [latino](https://github.com/primitivorm/latino)

`sudo apt-get install libssl-dev libcurl4-openssl-dev`

### Instalación
##### linux
```
git clone https://github.com/primitivorm/latino-curl
cd latino-curl
git submodule update --init --recursive
sudo chmod +x instalar.sh
sudo bash instalar.sh
```

#### Dependecias
[curl](https://github.com/curl/curl)

##### Uso de esta librería en código latino
```
//necesario para agregar la librería dinámica
incluir("curl")

//se realiza una petición a www.telegramforo.com y se muestra contenido
resp = curl.peticion("www.telegramforo.com")
escribir(resp)

//se codifica un texto y se realiza una búsqueda en google
busqueda = "perros y gatos"
resp = curl.peticion("https://www.google.com.mx/search?q=" .. curl.escape(busqueda))
escribir(resp)
```

##### Cualquier aportación o sugerencia es bienvenida
