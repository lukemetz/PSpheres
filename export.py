import bpy
import sys

bpy.ops.import_mesh.stl(filepath="Export.stl")

high = bpy.data.objects['Export']

high.name = 'mesh'

bpy.context.scene.objects.active = high
high.select = 1
bpy.ops.object.shade_smooth()
bpy.ops.object.editmode_toggle()
bpy.ops.wm.context_set_value(data_path="tool_settings.mesh_select_mode",value="(False, False, True)")
bpy.ops.mesh.select_all(action='SELECT')


bpy.ops.object.modifier_add(type='REMESH')

low.modifiers[0].octree_depth=3
low.modifiers[0].scale=.7
print(low.modifiers[0])

bpy.ops.object.modifier_apply(modifier="Remesh")

