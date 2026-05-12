A list of all things that can be added to the engine in the future.

Some can be done later in the project. Others will be over-engineering for this project.



\#Scene

* Add destroy with timer for :

  * Actor
  * Component
  * UIElement
* Rework component

  * ActorComponent who contains all logic (begin play, update, etc.)

    * (a virtual class virtual \~ActorComponent() = 0)
  * SceneComponent who contains all node logic
* Add SceneSubsystem for object living in the scene without node (for example managers)



\#Rendering

* 3D

  * Meshes
  * Transform 3D
  * Lights
* Implements Render command system

  * Allow for batch rendering
  * Avoid dynamic casting for UI Rendering
* Add visibility options



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

* Add a UserWidget/Canvas system and remove BeginPlay/Update from UIElement to be closer of UE

