extends Control

@export var cell_size: int = 50
@export var bg: Color = Color.BLACK
@export var cell_color: Color = "#0c1b49"
@export var fileDialog: FileDialog

@onready var rect_scene = preload("res://rect.tscn")
@onready var rect_container = $MatrixContainer

var max_alpha: int = 255
var max_matrix_value: int = 0
var matrix_size: int = 0
var matrix = []

# Called when the node enters the scene tree for the first time.
func _ready():
	fileDialog.current_dir = "../cmake-build-debug/"
	fileDialog.popup_centered_ratio(1)
	$Toolbar/Color/ColorPickerButton.color = cell_color
	

func _on_file_dialog_file_selected(path):
	var file_content = _open_file(path)

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
		
	create_matrix()
	
func _process(delta):
	pass
	

func create_matrix():
	var gap: int = cell_size / 10
	
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
				
				var weight: float = 0
				
				if(element != "0"):
					weight =  element.to_float() / max_matrix_value 
				
				var color = cell_color.lerp(cell_color.inverted(), weight)
				
				var rect = rect_scene.instantiate()
				rect.init(pos, color, element)
				rect_container.add_child(rect)
				cell_count += 1
			row_count += 1


func _on_h_slider_drag_ended(value_changed):
	var value = $Toolbar/HSlider.value
	var new_scale = Vector2.ONE * value / 100
	rect_container.scale = new_scale


func _on_h_slider_value_changed(value):
	$Toolbar/Value.text = str(value)


func _on_color_picker_button_color_changed(color):
	self.cell_color = color
	if max_matrix_value < 33:
			delete_children(rect_container)
			create_matrix()

static func delete_children(node):
	for n in node.get_children():
		node.remove_child(n)
		n.queue_free()


func _on_color_picker_button_popup_closed():
	delete_children(rect_container)
	create_matrix()


func _on_open_file_pressed():
	fileDialog.popup_centered_ratio(1)
