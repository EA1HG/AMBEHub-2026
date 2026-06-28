# AMBEHub

> Plataforma modular para la gestión de dispositivos AMBE y comunicaciones digitales.

---

## ¿Qué es AMBEHub?

AMBEHub es un servidor de nueva generación diseñado para compartir dispositivos AMBE entre múltiples clientes de forma eficiente, segura y escalable.

A diferencia de un servidor AMBE tradicional, AMBEHub se ha diseñado desde cero con una arquitectura modular que permitirá incorporar nuevas funcionalidades sin modificar el núcleo del sistema.

---

# Objetivos

- Compartir uno o varios dispositivos AMBE.
- Soportar múltiples usuarios simultáneamente.
- Gestionar sesiones independientes.
- Balancear la carga entre varios dispositivos.
- Incorporar un panel web de administración.
- Proporcionar una API para aplicaciones externas.
- Facilitar la ampliación mediante módulos.

---

# Estado del proyecto

Versión actual:

0.4.0

Actualmente el proyecto dispone de:

- Logger
- Config
- AMBEHubServer
- UDPServer
- Packet
- PacketDispatcher

---

# Arquitectura

            Cliente
               │
               ▼
          UDPServer
               │
            Packet
               │
      PacketDispatcher
               │
      Session Manager
               │
       Device Manager
               │
          AMBE Devices


---

# Roadmap

- v0.5 Cliente oficial
- v0.6 Session Manager
- v0.7 Login
- v0.8 Device Manager
- v0.9 Dashboard Web
- v1.0 Audio funcionando

---

# Compilación

```bash
mkdir build
cd build

cmake ..

make


---

# VERSION

---

# VERSION


0.4.0


---

# CHANGELOG.md

```markdown
# Changelog

## 0.4.0

### Añadido

- Arquitectura inicial.
- Logger.
- Config.
- UDP Server.
- Packet.
- PacketDispatcher.

### Estado

Servidor UDP completamente funcional.