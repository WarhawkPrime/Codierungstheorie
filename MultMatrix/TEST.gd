extends SubViewport
@onready var file_dialog: FileDialog = $"../../../FileDialog"
func _on_button_pressed():
	var img = self.get_texture().get_image()
	var filename = file_dialog.current_file.replace(".csv", "")
	return img.save_png(filename+".png")
