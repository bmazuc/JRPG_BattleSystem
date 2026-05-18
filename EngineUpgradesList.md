A list of all things that can be added to the engine in the future.

Some can be done later in the project. Others will be over-engineering for this project.



\#Persistance

* Add object living through levels

  * WorldSubsystems
  * Persistent UI

    * Add another widget collection and scene graph inside UISystem

      * Prevent Persistant and level UI to be hierarchicaly linked
    * Add UILayer (Persistant and Level) inside SpawnOptions



\#Scene

* Add destroy with timer for :

  * Actor
  * Component
  * UIElement



\#Rendering

* 3D

  * Meshes
  * Transform 3D
  * Lights
* Implements Render command system

  * Allow for batch rendering
  * Avoid dynamic casting for UI Rendering



\#Inputs

* Add keyboard inputs
* Add controller inputs



\#Shaders

* Add geometry shader handling.



\#Audio

* Add audio management



\#Animation

* add animations management



\#UI

* Differentiate "panel elements" that can have children et "leaf elements" that can't have children

