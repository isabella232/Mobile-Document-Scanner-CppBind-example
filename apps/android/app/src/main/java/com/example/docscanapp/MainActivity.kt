package com.example.docscanapp

import android.app.Activity
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import cv.*
import doc_scanner.DocCornerPointsExtractor
import doc_scanner.DocExtractor
import doc_scanner.saveImage
import android.widget.Button
import android.widget.ImageView
import androidx.activity.result.contract.ActivityResultContracts
import androidx.core.app.ActivityCompat
import androidx.core.content.FileProvider
import java.io.File

private lateinit var photoFile: File
private const val FILE_NAME = "photo.jpg"
private const val REQ_CODE = 111


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button = findViewById<Button>(R.id.button)

        button.isEnabled = false

        if (ActivityCompat.checkSelfPermission(
                this,
                android.Manifest.permission.CAMERA
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(android.Manifest.permission.CAMERA),
                REQ_CODE
            )
        } else {
            button.isEnabled = true

            button.setOnClickListener {
                val i = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
                photoFile = getPhotoFile(FILE_NAME)
                val fileProvider =
                    FileProvider.getUriForFile(this, "com.example.fileprovider", photoFile)
                i.putExtra(MediaStore.EXTRA_OUTPUT, fileProvider)
                getResult.launch(i)
            }
        }

    }


    private fun getPhotoFile(fileName: String): File {
        val storageDirectory = getExternalFilesDir(Environment.DIRECTORY_PICTURES)
        return File.createTempFile(fileName, ".jpg", storageDirectory)

    }

    private val getResult =
        registerForActivityResult(
            ActivityResultContracts.StartActivityForResult()
        ) {
            if (it.resultCode == Activity.RESULT_OK) {
                val image = imread(photoFile.absolutePath)
                val docCornersExtractor = DocCornerPointsExtractor()
                docCornersExtractor.image = image
                docCornersExtractor.computeCornerPoints()
                val docExtractor =
                    DocExtractor(docCornersExtractor.image, docCornersExtractor.points)
                val imgWarp = docExtractor.warp()
                saveImage(photoFile.absolutePath, imgWarp)

                val scan = BitmapFactory.decodeFile(photoFile.absolutePath)
                val imageView = findViewById<ImageView>(R.id.imageView)
                imageView.setImageBitmap(scan)


            }
        }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == REQ_CODE && grantResults.firstOrNull() == PackageManager.PERMISSION_GRANTED) {
            val button = findViewById<Button>(R.id.button)
            button.isEnabled = true
        }
    }
}