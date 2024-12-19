package com.example.lab4

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import kotlin.jvm.java


@Database(entities = [Participant::class], version = 1, exportSchema = false)
abstract class ParticipantDatabase : RoomDatabase() {
    abstract fun participantDao(): ParticipantDao


    companion object
    {

        @Volatile
        private var INSTANCE:ParticipantDatabase?=null

        private const val DATABASE_NAME="participant_db"

        @JvmStatic
        fun getDatabase(context: Context) :ParticipantDatabase
        {
            return INSTANCE?: synchronized(this)
            {
                val instance= Room.databaseBuilder(context.applicationContext,ParticipantDatabase::class.java,
                    DATABASE_NAME).build()
                INSTANCE=instance
                instance
            }

        }

    }
}
