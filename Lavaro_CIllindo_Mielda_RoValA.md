Corrección de la proyección escalar ('t') en la intersección rayo–cilindro
Proyección Escalar

Ejemplo de proyección vectorial: El vector verde 
𝑎
1
a
1
	​

 es la proyección de 
𝑎
a sobre el eje definido por 
𝑏
b. La longitud de 
𝑎
1
a
1
	​

 (proyección escalar) se calcula como 
𝑎
⋅
𝑏
^
a⋅
b
^
es.wikipedia.org
. En el contexto del cilindro, 
𝑎
a sería el vector desde la base del cilindro hasta el punto de impacto, y 
𝑏
b la dirección del eje (unitaria).

Para obtener la distancia proyectada alineada con el eje del cilindro, se debe proyectar el vector que va desde la base del cilindro hasta el punto de intersección sobre el vector unitario del eje. En fórmula:

𝑡
=
(
𝑃
impacto
−
𝐵
base
)
⋅
𝑢
^
eje
,
t=(P
impacto
	​

−B
base
	​

)⋅
u
^
eje
	​

,

donde 
𝐵
base
B
base
	​

 son las coordenadas de la base inferior del cilindro, 
𝑃
impacto
P
impacto
	​

 es la posición del punto de impacto calculada, y 
𝑢
^
eje
u
^
eje
	​

 es el vector de dirección del eje normalizado (unidad). Este producto punto (dot product) nos da la proyección escalar de 
𝑃
impacto
−
𝐵
base
P
impacto
	​

−B
base
	​

 sobre el eje
es.wikipedia.org
, es decir, la distancia a lo largo del eje desde la base hasta el punto. Si el eje está normalizado, t resulta directamente en unidades de longitud (por ejemplo, metros o la unidad de espacio utilizada) y variará de forma proporcional al desplazamiento del punto a lo largo del cilindro. En otras palabras, movimientos del punto de impacto hacia arriba o abajo por el lado del cilindro producirán cambios lineales correspondientes en t.

Importante: Asegúrate de que el vector de eje object.rotation esté normalizado (de longitud 1). Si no lo está, la fórmula debe ajustarse dividiendo por la magnitud del eje (o mejor, normalizarlo de antemano). Con un eje unitario, la proyección escalar es numéricamente más estable y tiene significado directo (distancia). Si el eje no es unitario, el valor 
(
𝑃
−
𝐵
)
⋅
𝑢
(P−B)⋅u estará escalado por la longitud de 
𝑢
u, causando que t sea demasiado grande o demasiado pequeño de forma consistente (y que cambie muy poco aunque 
𝑃
P varíe, o quede fuera de rango esperado). Por ejemplo, si 
𝑢
u tiene longitud 0.5, la proyección será la mitad de la distancia real, variando muy poco; si la longitud es 2, t saldrá el doble de la distancia real (a menudo excediendo la altura esperada). Por esto, siempre utiliza 
𝑢
^
eje
u
^
eje
	​

 unitario en el cálculo de t.

Validación de Rango

Una vez obtenida la proyección escalar t desde la base, podemos validar si el punto de impacto cae dentro del cuerpo del cilindro (excluyendo tapas) comprobando si t está dentro del rango de la altura del cilindro. Supongamos que la altura del cilindro es H (por ejemplo object.sizes.vs[1]):

Si t < 0, entonces el punto de impacto quedó antes o por debajo de la base del cilindro (un valor negativo indica que el punto proyecta por detrás de la base en la dirección del eje). En este caso, la intersección corresponde a la prolongación infinita por debajo del cilindro y no al tramo finito del cilindro. Debe descartarse para un cilindro finito sin tapa inferior.

Si t > H, el punto de impacto está más arriba de la tapa superior del cilindro (más allá de la altura). Esto significa que el rayo golpeó la extensión infinita del cilindro por encima del cilindro real. También debe descartarse (a menos que se estuviera considerando una tapa superior).

Solo si 
0
≤
𝑡
≤
𝐻
0≤t≤H, el punto de impacto se encuentra entre la base y la cima del cilindro, es decir, dentro del tramo lateral del cilindro. En tal caso, la intersección es válida sobre la superficie curva del cilindro (sin contar tapas).

En términos geométricos, un cilindro finito puede verse como un cilindro infinito recortado por dos planos (las bases). La comprobación anterior equivale a verificar que el punto de impacto esté entre el plano de la base inferior y el plano de la base superior. Dicho de otro modo, estamos asegurándonos de que la coordenada del punto a lo largo del eje cae dentro del segmento [0, H]. Si el valor t calculado sale fuera de este intervalo, significa que la intersección calculada pertenece en realidad fuera del cuerpo lateral: o bien por debajo de la base (t<0) o por encima de la altura (t>H). En esos casos, en un trazador de rayos se suele descartar esa solución de intersección para el cilindro finito (y eventualmente probar con la otra solución del rayo, o reportar que no hay impacto con el cuerpo lateral).

Nota: Si el cilindro tuviera tapas y quisiéramos considerarlas, entonces una intersección con t fuera de [0, H] podría indicar un impacto en una de las tapas. En ese caso habría que hacer una comprobación aparte: intersecar el rayo con el plano de la base inferior o superior y comprobar si cae dentro del círculo (radio) de la tapa. Sin embargo, dado que aquí nos enfocamos en el cilindro sin tapas, simplemente descartamos las soluciones fuera del rango.

Además, es importante considerar la orientación del eje. La fórmula asume que 
𝑢
^
eje
u
^
eje
	​

 apunta desde la base hacia la dirección del cilindro (hacia la tapa superior). Si por alguna razón el vector de eje estuviera invertido (apuntando de la tapa hacia la base), el valor t calculado saldría negativo para puntos que en realidad están dentro del cilindro. En tal caso, la condición debería invertirse o preferiblemente se debe unificar la orientación: por ejemplo, asegurarse al definir el objeto que object.coords es la base inferior y object.rotation apunta hacia arriba (hacia la segunda base). Mantener esta convención evita confusiones, pues así un 0 <= t <= H siempre indica correctamente que el punto está entre las dos bases.

Ejemplo de Código

A continuación se muestra un ejemplo simplificado de cómo integrar este cálculo en una función de intersección rayo–cilindro. Supondremos que ya se resolvió la intersección con el cilindro infinito (por ejemplo, mediante la fórmula cuadrática correspondiente a la superficie lateral), obteniendo uno o dos puntos de impacto candidatos. Luego aplicamos la validación de rango con la proyección escalar:

// Datos del cilindro (definidos en el objeto):
vec3 base = object.coords;                   // base inferior del cilindro
vec3 axis = normalize(object.rotation);      // eje del cilindro (vector unitario)
float H    = object.sizes.vs[1];             // altura del cilindro (distancia de base a tope)
float R    = object.sizes.vs[0];             // radio del cilindro (suponiendo que vs[0] sea el radio)

// ... (cálculo de intersección con cilindro infinito, obteniendo t_ray como distancia del rayo al punto de impacto) ...

vec3 P = rayOrigin + t_ray * rayDirection;   // coordenadas del punto de impacto sobre el rayo
float t_axis = dot(P - base, axis);          // proyección escalar de base->P sobre el eje

// Validar que P esté dentro de los límites del cilindro finito (entre las bases):
if (t_axis < 0.0f || t_axis > H) {
    // La intersección cae fuera del tramo del cilindro (antes de la base o más allá de la altura)
    // Descartar este impacto para el cilindro sin tapas.
    return false; // (o continuar con la siguiente solución si existe)
}

// Si se llega aquí, t_axis está dentro [0, H], lo que indica que P está sobre el lado del cilindro.
// Podemos devolver el punto de impacto válido:
hit.tRay = t_ray;        // distancia desde el origen del rayo hasta P
hit.point = P;           // posición del impacto
hit.normal = ...         // normal en el punto (calcular según P, base y eje)
return true;


En este código, t_axis corresponde a la variable 't' de la pregunta: representa cuánto se ha avanzado desde la base a lo largo del eje del cilindro hasta el punto de impacto. Primero normalizamos el eje (axis) para garantizar que la comparación con la altura H sea coherente. Luego calculamos la posición de impacto P utilizando el parámetro t_ray obtenido al resolver la ecuación de intersección del rayo con el cilindro infinito. A partir de P, obtenemos t_axis con el producto escalar mencionado. Finalmente, descartamos la solución si t_axis está fuera del rango [0, H].

Geometría de la normal: (Por completar el ejemplo) La normal del cilindro en el punto de impacto se puede calcular proyectando el vector desde el eje hacia el punto. Una forma práctica es: tomar el vector radial P - base - t_axis * axis (que sería equivalente a restarle a 
𝑃
−
𝐵
P−B su componente axial, quedando el componente perpendicular al eje), y luego normalizarlo para obtener la dirección normal. Esto resulta en una normal perpendicular al eje, apuntando hacia afuera del cilindro. (Esta normal no está definida en los extremos si uno llega exactamente a las tapas, pero en este caso sin tapas no hay problema). Asegurarse de usar t_axis calculado correctamente es clave también para el cálculo de la normal.

Consideraciones Numéricas

Al implementar estos cálculos es importante tener en cuenta algunos detalles numéricos para garantizar estabilidad y exactitud:

Uso de punto flotante: El cálculo de t_axis involucra productos y restas de números de punto flotante. Aunque es sencillo, pueden ocurrir pequeños errores de redondeo. Por ejemplo, un punto de impacto que teóricamente está justo en la base podría dar un t_axis ligeramente negativo (
−
10
−
8
−10
−8
 por ejemplo) debido a errores numéricos. Conviene entonces, al verificar los límites, considerar un margen de tolerancia (epsilon). Por ejemplo, en vez de t_axis < 0 podría usarse t_axis < -EPS (con EPS muy pequeño, e.g. 1e-6) para no descartar por error intersecciones válidas que caen prácticamente en el borde. Lo mismo para el límite superior: permitir una mínima tolerancia cuando 
𝑡
𝑎
𝑥
𝑖
𝑠
t
a
	​

xis está muy próximo a H. Esto previene falsos negativos debidos al redondeo.

Normalización del eje: Ya se mencionó, pero numéricamente es fundamental: incluso si object.rotation debería ser unitario por construcción, es prudente normalizarlo (al menos una vez fuera del bucle de trazado) para corregir cualquier desviación por almacenamiento o cálculos previos. Un eje con norma distinta de 1 escalará t linealmente (por esa norma) y podría causar que un punto válido no pase la validación de rango. La normalización elimina ese factor de escala.

Estabilidad de la solución del cilindro infinito: Aunque la pregunta se centra en la proyección, cabe mencionar que la obtención de la intersección con el cilindro infinito (resolviendo la ecuación cuadrática) también tiene sus propias consideraciones numéricas. Por ejemplo, cuando el rayo es casi paralelo al eje del cilindro, la componente perpendicular (D_{\perp} en la ecuación) será muy pequeña, lo que puede llevar a soluciones con valores de t_ray grandes o inestables. En tales casos, asegurarse de usar precisión suficiente (double en lugar de float si es necesario) y manejar condiciones límite (rayos paralelos que nunca intersectan el lado) es importante. Una vez obtenido un t_ray confiable, el cálculo de t_axis con el producto punto suele ser robusto, siempre que el eje esté normalizado.

Consistencia de unidades y marcos de referencia: Verifica que todos los vectores estén en el mismo sistema de coordenadas. Es decir, rayOrigin, rayDirection, object.coords (base) y object.rotation (eje) deben estar todos en coordenadas de mundo (u otro espacio común). Si el cilindro se define en espacio de objeto y no se ha transformado el rayo a ese espacio, el cálculo de t podría ser incorrecto. Una práctica común en ray tracing es transformar el rayo al espacio local del objeto donde la geometría está definida de forma sencilla (por ejemplo, cilindro alineado con un eje conocido). Por ejemplo, muchos implementan el cilindro alineándolo con el eje Z en su espacio local
pbr-book.org
pbr-book.org
, de modo que la proyección escalar es simplemente la coordenada 
𝑧
z del punto de impacto en ese sistema. Si se sigue ese enfoque, recuerda transformar de vuelta el punto al mundo tras la intersección. En cualquier caso, cuando calcules t_axis = dot(P - base, axis), asegúrate de que P, base y axis están definidos en el mismo espacio. Un error de desalineación de espacio puede producir resultados aparentemente erráticos para t.

En resumen, para corregir la computación de t y lograr que varíe de forma estable y proporcionada a la altura del cilindro, debes: (1) restar la posición de la base al punto de impacto, (2) proyectar usando el eje normalizado mediante el producto escalar, y (3) usar ese valor para verificar los límites [0, altura]. Siguiendo estos pasos, la variable t representará correctamente la distancia a lo largo del eje dentro del cilindro, aumentando linealmente desde 0 (en la base) hasta H (en la tapa), y permitirá filtrar intersecciones que no caen en el tramo válido del cilindro. Con esta corrección, notarás que t cambiará de manera intuitiva cuando el punto de impacto se desplace a diferentes alturas del cilindro, y raramente deberá salir del rango salvo que el rayo realmente pase por un extremo del cilindro. Esto resolverá el comportamiento extraño original y hará la intersección rayo–cilindro geométricamente coherente