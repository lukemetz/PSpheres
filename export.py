import bpy
import sys

for i in range(10):
  bpy.ops.import_mesh.stl(filepath="Export."+str(i)+".stl")

  high = bpy.data.objects['Export.'+str(i)]

  high.name = 'mesh'+str(i)

  bpy.context.scene.objects.active = high
  high.select = 1
  bpy.ops.object.shade_smooth()
  high.active_material = bpy.data.materials['black']
  x = i%5
  y = i/5;
  high.location[0] += x*3;
  high.location[1] += y*3;
#bpy.ops.object.editmode_toggle()
#bpy.ops.wm.context_set_value(data_path="tool_settings.mesh_select_mode",value="(False, False, True)")
#bpy.ops.mesh.select_all(action='SELECT')


#bpy.ops.object.modifier_add(type='REMESH')

#high.modifiers[0].octree_depth = 4
#high.modifiers[0].scale = .9
#high.modifiers[0].mode = "SMOOTH"

#bpy.ops.object.modifier_apply(modifier="Remesh")

