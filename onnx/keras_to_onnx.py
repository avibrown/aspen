import os
os.environ['TF_KERAS'] = '1'
import onnxmltools

import tensorflow as tf

"""
Convert to SavedModel format
"""
model = tf.keras.models.load_model(f'{os.getcwd()}/model.h5')
tf.keras.models.save_model(model, f'{os.getcwd()}/saved_model')

"""
...and then to ONNX
"""
model = tf.keras.models.load_model('saved_model')
onnx_model = onnxmltools.convert_keras(model) 

onnxmltools.utils.save_model(onnx_model, 'onnx')