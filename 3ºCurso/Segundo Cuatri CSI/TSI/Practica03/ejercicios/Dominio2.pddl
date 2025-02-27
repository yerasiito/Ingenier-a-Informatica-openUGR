(define (domain starcrfd2)
    (:requirements :strips :typing :fluents :negative-preconditions :conditional-effects :disjunctive-preconditions)
    (:types
        ;; Los recursos no tienen objetos, solo tipos de recursos
        ;; Las unidades y los edificios pueden ser instanciados, por eso hay tipo y no tipos.
        Unidad tipoUnidad Edificio tipoEdificio Localizacion tipoRecurso - object
    )
    (:constants 
        ; subclases de cada objeto. Se añade extractores
        VCE - tipoUnidad
        CentroDeMando Barracones Extractor - tipoEdificio
        Minerales Gas - tipoRecurso
    )
    (:predicates
        ;; Un edificio, Unidad o Recurso esta en una Localizacion concreta
        (en ?e - object ?l - Localizacion)

        ;; Existe un camino entre dos localizaciones
        ;; Conectar dos localizaciones para formar el grid
        (conectado ?l1 - Localizacion ?l2 - Localizacion)
        
        ;; No se necesita para el ejercicio, todavia
        ;; (Construido ?e - Edificio)

        ;; VCE extrae un tipo de recurso
        (estaExtrayendo ?v - Unidad)

        ; El recurso se extrae y está disponible (se asume ilimitado)
        (extrayendoRecurso ?r - tipoRecurso)

        ; Tipo de edificio
        (esTipoEdificio ?e - edificio ?t - tipoEdificio)

        ; Tipo de Unidad
        (esTipoUnidad ?u - unidad ?t - tipoUnidad)

        ; Recursos que el edificio necesita
        (necesita ?te - tipoEdificio ?tr - tipoRecurso)
    )
    
    ;; Navegar: mueve una unidad entre dos localizaciones
    ;; Parámetros: Unidad, Localizacion Origen, Localizacion destino
    (:action Navegar
        :parameters (?v - Unidad ?lorig - Localizacion ?ldest - Localizacion)
        :precondition
            (and
                ; Unidad esta en origen
                (en ?v ?lorig)
                ; Origen y destino estan conectados
                (conectado ?lorig ?ldest)
            )
        :effect
            (and
                ; Unidad se mueva a destino
                (en ?v ?ldest)
                ; Unidad ya no está en origen
                (not (en ?v ?lorig))
            )
    )

    ;; Asignar: asigna un VCE a un nodo recurso
    ;; Parámetros: Unidad, Localización del recurso
    (:action Asignar
        :parameters (?u - Unidad ?l - Localizacion)
        :precondition
            (and
                ; La unidad está en la localización
                (en ?u ?l)

                ; O bien extrae Minerales o Gas
                (or
                    (exists (?e - edificio)
                        (and 
                            (esTipoEdificio ?e Extractor) ; Es un extractor
                            (en ?e ?l) ; El edificio está en la localización
                            (en Gas ?l) ; El gas está en la localización
                        )
                    )
                    (not (en Gas ?l)) ; Si no es gas, no necesita edificio
                )
            )
        :effect
            (and
                ; La unidad extrae y no hace otra cosa más
                (estaExtrayendo ?u)
                
                ; Si hay un desposito de minerales en ?l, extrae minerales
                (when (and (en Minerales ?l))
                    (and
                        (ExtrayendoRecurso Minerales)
                    ) 
                )

                ; Si hay un desposito de gas en ?l, extrae gas
                (when (and (en Gas ?l))
                    (and
                        (ExtrayendoRecurso Gas)
                    )
                )
            )
    )

    ;; Construir: construye un Edificio en un nodo
    ;; Parámetros: Unidad, Edificio, Localizacion, tipoRecurso
    (:action Construir
      :parameters (?u - Unidad ?e - Edificio ?l - Localizacion ?tr - tipoRecurso)
      :precondition
         (and
            ; La unidad no está ocupada extrayendo
            (not (estaExtrayendo ?u))
            
            ; El edificio necesita recursos especificos de su tipo
            (exists (?te - tipoEdificio)
               (and 
                  (esTipoEdificio ?e ?te) ; es un edificio del tipo requerido
                  (necesita ?te ?tr) ; necesita un tipo de recurso específico
                  (extrayendoRecurso ?tr) ; dispone del recurso necesario
               )
            )
            ; Unidad está en la localización para construir
            (en ?u ?l)
         )
      :effect
         (and
            ; Se construye el edificio
            (en ?e ?l)
         )
   )
)