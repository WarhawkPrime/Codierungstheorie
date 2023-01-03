extends Control

@export var cell_size: int = 50

## Use pretty or fast rendering
@export var fast: bool = false
@export var font: Font

@export var cell_color: Color = "#0c1b49"

@export var fileDialog: FileDialog

@onready var target_viewport = get_tree().root.get_viewport()
@onready var rect_scene = preload("res://MatrixCell.tscn")
@onready var rect_container = $MatrixContainer

@onready var default_cell_size = cell_size


var max_alpha: int = 255
var max_matrix_value: int = 0
var matrix_size: int = 0
var matrix = []




func save_to():
	var img: Image = get_viewport().get_texture().get_image()
	return img.save_png("test.png")


# Called when the node enters the scene tree for the first time.
func _ready():
	fileDialog.current_dir = "../cmake-build-debug/"
	fileDialog.popup_centered_ratio(1)
	$Toolbar/Color/ColorPickerButton.color = cell_color


func _on_file_dialog_file_selected(path):
	_open_file(path)

func _open_file(path):
	matrix = []
	var file: FileAccess = FileAccess.open(path, FileAccess.READ)
	var header = file.get_csv_line(";")
	matrix_size = header.size() -1
	while (!file.eof_reached()):
		var csv = file.get_csv_line(";")
		print("Processing line %s" % csv[0])
		var values = csv.slice(1)
		for i in values:
			if i.to_int() > max_matrix_value:
				max_matrix_value = i.to_int()
		if(values.size()==0):
			break;
		matrix.push_back(values)

	print_debug(max_matrix_value)
	print_debug(matrix_size)

	if(fast):
		queue_redraw()
	else:
		create_matrix()


func _draw():
	var gap: int = cell_size / 10

	var start: int = Time.get_ticks_usec()
	if(matrix.size() != 0):
		print("Creating matrix")
		var row_count: int = 0
		for row in matrix:
			print("Processing row %s of %s" % [row_count, matrix_size])
			var cell_count: int = 0
			for element in row:
				var x: int = cell_size+(cell_size*row_count)+ gap * row_count
				var y: int = cell_size+(cell_size*cell_count) + gap * cell_count

				x += 100
				y += 100

				var color = calculate_dynamic_color(element.to_float(), self.cell_color)
				var rext = Rect2(x, y, cell_size, cell_size)
				draw_rect(rext, color)
				cell_count += 1
			row_count += 1
			var finish: int = Time.get_ticks_usec()
		var finish: int = Time.get_ticks_usec()
		var drawn_in_ms = (finish - start)

		print("Drawn in: ", drawn_in_ms / 1000)


func create_matrix():
	var gap: int = 2

	var rects = []
	var start: int = Time.get_ticks_usec()
	if(matrix.size() != 0):
		print("Creating matrix")
		var row_count: int = 0
		for row in matrix:
			print("Processing row %s of %s" % [row_count, matrix_size])
			var cell_count: int = 0
			for element in row:
				var x: int = cell_size+(cell_size*row_count)+ gap * row_count
				var y: int = cell_size+(cell_size*cell_count) + gap * cell_count
				var pos: Vector2 = Vector2(x, y)

				var color = calculate_dynamic_color(element.to_float(), self.cell_color)

				var rect = rect_scene.instantiate()
				rect.init(pos, color, element.to_int())
				rects.append(rect)

				cell_count += 1
			row_count += 1

	var finish_creating: int = Time.get_ticks_usec()

	print_debug(rects.size())

	for rect in rects:
		rect_container.add_child(rect)

	var finish: int = Time.get_ticks_usec()

	var created_ms = (finish_creating - start)
	var added_ms = (finish - start)
	var delta_ms = added_ms - created_ms

	print("Created: ", created_ms / 1000 )
	print("Added: ", added_ms / 1000)
	print("Delta: ", delta_ms / 1000)


func calculate_dynamic_color(value: float, color: Color):
	var weight: float = 0
	if(value != 0):
		weight = value / max_matrix_value

	return color.lerp(color.inverted(), weight)

func _on_h_slider_drag_ended(value_changed):
	var value = $Toolbar/HSlider.value
	print(value)
	var new_scale = Vector2.ONE * value / 1000
	if(fast):
		cell_size = default_cell_size * ( value / 1000 )
		queue_redraw()
	else:
		rect_container.scale = new_scale


func _on_h_slider_value_changed(value):
	$Toolbar/Value.text = str(value)


func _on_color_picker_button_color_changed(color):
	self.cell_color = color
	if(fast):
		queue_redraw()
	else:
		var rects: Array = rect_container.get_children()
		for rect in rects:
			var new_color = calculate_dynamic_color(rect.value, color)
			rect.change_color(new_color)

func _on_open_file_pressed():
	delete_children(rect_container)
	fileDialog.popup_centered_ratio(1)


static func delete_children(node):
	for n in node.get_children():
		node.remove_child(n)
		n.queue_free()


func _on_button_pressed():
	save_to()

func _on_value_text_submitted(new_text):
	var string_val: String = new_text
	$Toolbar/HSlider.value = string_val.to_int()
	_on_h_slider_drag_ended(string_val.to_int())
