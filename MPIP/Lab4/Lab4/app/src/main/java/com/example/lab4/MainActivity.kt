package com.example.lab4

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import com.example.lab4.databinding.ActivityMainBinding
import kotlinx.coroutines.*

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    private lateinit var database: ParticipantDatabase
    private lateinit var participantDao: ParticipantDao
    private lateinit var adapter: ParticipantAdapter
    private val participants = mutableListOf<Participant>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        //TODO 3: here initialize the database, participantDao and adapter

        //TODO 6: here set the RecyclerView's layout manager and adapter


        binding.addButton.setOnClickListener {
            val name = binding.editText.text.toString()
            //TODO 7: add a participant if the name is not empty
        }

        binding.assignButton.setOnClickListener { assignSecretSantas() }
        fetchParticipants()
    }

    private fun fetchParticipants() {
        CoroutineScope(Dispatchers.IO).launch {
            val allParticipants = participantDao.getAllParticipants()
            withContext(Dispatchers.Main) {
               adapter.updateParticipants(allParticipants)
            }
        }
    }

    private fun addParticipant(participant: Participant) {
    //TODO 9: add a participant to the database asynchronously using Kotlin Coroutines -
    // use the coroutine dispatcher for input/output operations and
    // make sure to call fetchParticipants() after adding the participant
    }

    private fun deleteParticipant(participant: Participant) {
    //TODO 10: delete a participant from the database asynchronously using Kotlin Coroutines -
    // use the coroutine dispatcher for input/output operations and
    // make sure to call fetchParticipants() after removing the participant
    }

    private fun assignSecretSantas() {
        //TODO 11: Check if there are at least 2 participants

        val shuffledList = participants.shuffled()
        val assignments = shuffledList.zipWithNext() + Pair(shuffledList.last(), shuffledList.first())

        val message = assignments.joinToString("\n") { "${it.first.name} -> ${it.second.name}" }
        val alertDialog = AlertDialog.Builder(this)
            .setTitle("Secret Santa Assignments")
            .setMessage(message)
            .setPositiveButton("OK", null)
            .create()

        alertDialog.setOnShowListener{
            alertDialog.window?.setBackgroundDrawableResource(R.color.background_red)
            val titleView = alertDialog.findViewById<TextView>(android.R.id.title)
            titleView?.setTextColor(ContextCompat.getColor(this, R.color.primary_red))
            val messageView = alertDialog.findViewById<TextView>(android.R.id.message)
            messageView?.setTextColor(ContextCompat.getColor(this, R.color.primary_red))
            alertDialog.getButton(AlertDialog.BUTTON_POSITIVE).apply {
                setTextColor(ContextCompat.getColor(this@MainActivity, android.R.color.holo_red_light))
            }
        }
        alertDialog.show()
    }
}
