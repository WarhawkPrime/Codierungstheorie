extends ColorRect

func init(pos: Vector2, color: Color, text: String, scale: Vector2 = Vector2(1, 1)):
	self.color = color
	self.scale = scale
	self.position = pos

	var label: Label = $Label
	label.text = text
	label.modulate = color.inverted()
	label.label_settings.outline_color = Color.BLACK
