extends ColorRect
class_name MatrixCell


var value:int = 0

func init(pos: Vector2, color: Color, value: int):
	self.color = color
	self.position = pos
	self.value = value

	var label: Label = $Label
	label.text = str(value)
	label.modulate = color.inverted()
	label.label_settings.outline_color = Color.BLACK

func change_color(color: Color):
	self.color = color
	$Label.modulate = color.inverted()
